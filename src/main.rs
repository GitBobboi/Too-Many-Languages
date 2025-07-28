extern "C" {
    fn fort();
}

fn main() {
    unsafe {
        fort();
    }
}