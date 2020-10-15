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
		.shared_flag(true)
		.compile("points");
}

fn main() {
	println!("cargo:rerun-if-changed=build.rs");

	macro_rules! source_check { () => {"cargo:rerun-if-changed=src/{}"} };
	println!(source_check!(), "cloud.hpp");
	println!(source_check!(), "point_cloud.hpp");
	println!(source_check!(), "point_iters.hpp");
	println!(source_check!(), "link.h");
	println!(source_check!(), "points.hpp");

	build_bindings();
	build_lib();
}
