task('default', ['clean', 'build', 'test']);

task('clean', function() {
    console.log('Cleaning...')
    var cmds = [
        'node-gyp clean'
    ];
    jake.exec(cmds, function () {
        console.log('Cleaning done.');
        complete();
    }, {
        stdout: true,
        stderr: true
    });
}, {async: true});


task('build',function () {
    console.log('Building...')
    var cmds = [
        'node-gyp configure',
        'node-gyp build'
    ];
    jake.exec(cmds, function () {
        console.log('Building done.');
        complete();
    }, {
        stdout: true,
        stderr: true
    });
}, {async: true});


task('test', function() {
    console.log('Testing...');
    var cmds = [
        'jasmine-node test/spec'
    ];
    jake.exec(cmds, function () {
        console.log('Testing done.');
        complete();
    }, {
        stdout: true,
        stderr: true,
        breakOnError: false
    });
}, {async: true});