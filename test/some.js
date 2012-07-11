
Object.defineProperty(JSON, 'prototype', {
    value: null,
    configurable: true
});

//delete Function.prototype

console.log((function() {}).length)