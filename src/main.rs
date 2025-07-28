extern "C" {
    fn fort();
}

fn main() {
    unsafe {
        fort();
    }
    println!("Hello from rust!")
}