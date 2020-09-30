extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn build_bindings() {
	let bindings = bindgen::Builder::default()
		.header("src/link.hpp")
		.parse_callbacks(Box::new(bindgen::CargoCallbacks))
		.generate()
		.unwrap();
	let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
	bindings
		.write_to_file(out_path.join("bindings.rs")).unwrap();
}

fn build_lib() {
	cc::Build::new()
		.cpp(true)
		.file("src/points.cpp")
		.include("src")
		.compile("points");
}

fn main() {
	println!("cargo:rerun-if-changed=build.rs");
	println!("cargo:rerun-if-changed=src/link.hpp");
	println!("cargo:rerun-if-changed=src/points.cpp");
	build_bindings();
//	build_lib();
}
