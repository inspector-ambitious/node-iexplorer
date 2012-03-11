// Copyright (c) 2012, Nicolas Ferrero
// All rights reserved.
//
// Author(s): Nicolas Ferrero <nico@sencha.com>
//
// You may use this file under the terms of the New BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Nicolas Ferrero nor the
//       names of contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL ARTUR ADIB BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "web_browser.h"

using namespace v8;

Persistent<Function> WebBrowserWrap::constructor;

// Load a headless IE
WebBrowserWrap::WebBrowserWrap(const v8::Arguments& args) {
  OleInitialize(NULL);
  HRESULT hr;
  w_ = NULL;
  
  hr = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_SERVER, IID_IWebBrowser2, (LPVOID*)&w_);
  if (SUCCEEDED(hr) && (w_ != NULL)) {
    w_->put_Visible(VARIANT_TRUE);
    w_->put_MenuBar(VARIANT_FALSE);
    w_->put_ToolBar(VARIANT_FALSE);
    w_->put_StatusBar(VARIANT_FALSE);
  } else if (w_) {
    w_->Quit();
  }
}

WebBrowserWrap::~WebBrowserWrap() {
  delete w_;
}

void WebBrowserWrap::Initialize(Handle<Object> target) {
  
  // constructor
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  
  tpl->SetClassName(String::NewSymbol("WebBrowser"));
  
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("open"),
    FunctionTemplate::New(Open)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("close"),
    FunctionTemplate::New(Close)->GetFunction());


  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("WebBrowser"), constructor);
}

Handle<Value> WebBrowserWrap::New(const Arguments& args) {
  HandleScope scope;

  WebBrowserWrap* w = new WebBrowserWrap(args);
  w->Wrap(args.This());

  return scope.Close(args.This());
}


Handle<Value> WebBrowserWrap::Open(const Arguments& args) {
  HandleScope scope;
  WebBrowserWrap* w = ObjectWrap::Unwrap<WebBrowserWrap>(args.This());
  IWebBrowser2* webBrowser = w->GetWrapped();
  BSTR oURL = SysAllocString(reinterpret_cast<const OLECHAR*>(*v8::String::Value(args[0]->ToString())));
  VARIANT var;
  
  var.vt = VT_EMPTY;
  webBrowser->Navigate(oURL, &var, &var, &var, &var);
  SysFreeString(oURL);
  
  return scope.Close(Undefined());
}

Handle<Value> WebBrowserWrap::Close(const Arguments& args) {
  HandleScope scope;
  WebBrowserWrap* w = ObjectWrap::Unwrap<WebBrowserWrap>(args.This());
  IWebBrowser2* webBrowser = w->GetWrapped();

  if (webBrowser) {
    webBrowser->Quit();
    webBrowser->Release();
  }
  OleUninitialize();
  return scope.Close(Undefined());
}