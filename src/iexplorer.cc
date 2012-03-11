#define _WINSOCKAPI_ /* disable winsock.h */
#include <comutil.h>
#include <exdisp.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <v8.h>



using namespace v8;

Handle<Value> Open(const Arguments& args) {
  HandleScope scope;
  OleInitialize(NULL);
  HRESULT hr;
  IWebBrowser2* pWebBrowser = NULL;
  hr = CoCreateInstance (CLSID_InternetExplorer, NULL, CLSCTX_SERVER, IID_IWebBrowser2, (LPVOID*)&pWebBrowser);
  
  if (SUCCEEDED(hr) && (pWebBrowser != NULL)) {
    BSTR oURL;
    VARIANT var;
    oURL = SysAllocString(L"http://www.google.com");
    var.vt = VT_EMPTY;
    pWebBrowser->put_Visible(VARIANT_TRUE);
    pWebBrowser->put_MenuBar(VARIANT_FALSE);
    pWebBrowser->put_ToolBar(VARIANT_FALSE);
    pWebBrowser->put_StatusBar(VARIANT_FALSE);
    pWebBrowser->Navigate(oURL, &var, &var, &var, &var);
    SysFreeString(oURL);
  } else if (pWebBrowser) {
    pWebBrowser->Release();
  }

  OleUninitialize();
  return scope.Close(String::New("world"));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "open", Open);
}

NODE_MODULE(iexplorer, init);