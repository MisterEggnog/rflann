/*
See end of file for license
*/
extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn build_bindings() {
	let bindings = bindgen::Builder::default()
		.header("src/link.h")
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

/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
