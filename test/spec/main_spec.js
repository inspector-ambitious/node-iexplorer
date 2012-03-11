describe("browser", function() {
    var ie = require(__dirname + "/../../src/iexplorer");
    
//    it ("should do something", function() {
//        
//    });
//    
//    beforeEach(function() {
//         
//
//    });
    
    describe("open", function() {
        it("should open the webpage", function() {
            browser = ie.open('../fixtures/test.html');
        });
    });
    
//    describe("getHTML", function() {
//        it("should return the page html", function() {
//            expect(browser.getHTML()).toEqual('<div>Test 1</div>');
//        });
//    });    
});