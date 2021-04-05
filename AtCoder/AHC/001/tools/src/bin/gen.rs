#![allow(non_snake_case)]

use rand::prelude::*;
use proconio::*;
use std::{collections::BTreeSet, io::prelude::*};

fn gen(name: String, seed: u64) -> std::io::Result<()> {
	eprintln!("generating {}", name);
	let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
	let mut f = std::io::BufWriter::new(std::fs::File::create(format!("in/{}", name))?);
	let n = (50.0 * 4.0f64.powf(rng.gen::<f64>())).round() as usize;
	let mut ps = vec![];
	let mut used = BTreeSet::new();
	for _ in 0..n {
		loop {
			let x = rng.gen_range(0, 10000);
			let y = rng.gen_range(0, 10000);
			if used.insert((x, y)) {
				ps.push((x, y));
				break;
			}
		}
	}
	let mut q = rand::seq::index::sample(&mut rng, 10000 * 10000 - 1, n - 1).into_iter().map(|a| a + 1).collect::<Vec<_>>();
	q.sort();
	q.insert(0, 0);
	q.push(10000 * 10000);
	let mut r = vec![];
	for i in 0..n {
		r.push(q[i + 1] - q[i]);
	}
	writeln!(f, "{}", n)?;
	for i in 0..n {
		writeln!(f, "{} {} {}", ps[i].0, ps[i].1, r[i])?;
	}
	Ok(())
}

fn main() -> std::io::Result<()> {
	if !std::path::Path::new("in").exists() {
		std::fs::create_dir("in")?;
	}
	let mut id = 0;
	while !is_stdin_empty() {
		input!{
			seed: u64
		}
		gen(format!("{:04}.txt", id), seed)?;
		id += 1;
	}
	Ok(())
}
