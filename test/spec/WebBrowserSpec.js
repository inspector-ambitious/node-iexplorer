describe("WebBrowser", function() {
    var WebBrowser = require(__dirname + "/../../build/Release/iexplorer").WebBrowser;
    
    describe("open", function() {
        var ie;

        beforeEach(function() {
            ie = new WebBrowser();
        });

        afterEach(function() {
            ie.close();
        });
        
        describe("opening an url", function() {
            it("should not throw any error", function() {
                expect(function() {
                    ie.open('http://www.github.com');  
                }).not.toThrow();
            });
        });

        describe("open without any arguments", function() {
            it("should throw an error", function() {
                expect(function() {
                    ie.open();
                }).toThrow("First argument must be a string");
            });
        });
    });
});