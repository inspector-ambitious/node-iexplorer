describe("WebPage", function() {
    var ie = require(__dirname + "/../../src/iexplorer"),
        webPage;
    
    it ("should do something", function() {
        
    });
    
    beforeEach(function() {
        webPage = new ie.WebPage({
            url: '../fixtures/test.html'
        }); 
    });
    
    describe("getHTML", function() {
        it("should return the page html", function() {
            expect(webPage.getHTML()).toEqual('<div>Test 1</div>');
        });
    });    
});