function js() {
    console.log("Hello from JS");
}

const args = process.argv.slice(1);
if (args[0] === "js") {
    js();
}