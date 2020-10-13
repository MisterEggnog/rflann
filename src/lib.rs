
mod bindings;

#[derive(Debug)]
pub struct PointCloud();

pub struct PointCloudIter<'a>(std::marker::PhantomData<&'a PointCloud>);

#[cfg(test)]
mod tests {
}
