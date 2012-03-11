describe("WebBrowser", function() {
    var WebBrowser = require(__dirname + "/../../build/Release/iexplorer").WebBrowser;
    
    describe("Load github.com", function() {
        it("should not throw any error", function() {
            expect(function() {
                var ie = new WebBrowser();
                ie.open('http://www.github.com');
                ie.close();
            }).not.toThrow();
        });
    });
     
});