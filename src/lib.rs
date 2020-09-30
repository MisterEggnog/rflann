#[repr(C, packed)]
pub struct Vector {
	x: i64,
	y: i64,
	z: i64,
}

pub struct ChunkPoints {
	points: Vec<Vector>,
}

impl Vector {

	#[inline]
	pub fn new(x: i64, y: i64, z: i64) -> Vector {
		Vector{x, y, z}
	}

	#[inline]
	pub fn get_x(&self) -> i64 {
		self.x
	}

	#[inline]
	pub fn get_y(&self) -> i64 {
		self.y
	}

	#[inline]
	pub fn get_z(&self) -> i64 {
		self.z
	}

}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
