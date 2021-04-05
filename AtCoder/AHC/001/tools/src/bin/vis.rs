#![allow(non_snake_case)]

use proconio::{input, source::*};

pub const W: i64 = 10000;

#[derive(Clone, Debug)]
pub struct Input {
	pub ps: Vec<(i64, i64)>,
	pub size: Vec<i64>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Rect {
	pub x1: i64,
	pub x2: i64,
	pub y1: i64,
	pub y2: i64,
}

impl Rect {
	pub fn size(&self) -> i64 {
		(self.x2 - self.x1) * (self.y2 - self.y1)
	}
}

pub fn intersect(r1: &Rect, r2: &Rect) -> bool {
	r1.x2.min(r2.x2) > r1.x1.max(r2.x1) && r1.y2.min(r2.y2) > r1.y1.max(r2.y1)
}

pub fn score(input: &Input, out: &Vec<Rect>) -> i64 {
	let n = input.ps.len();
	let mut score = 0.0;
	for i in 0..n {
		if out[i].x1 < 0 || out[i].x2 > W || out[i].y1 < 0 || out[i].y2 > W {
			eprintln!("rectangle {} is out of range", i);
			return 0;
		}
		if out[i].x1 >= out[i].x2 || out[i].y1 >= out[i].y2 {
			eprintln!("rectangle {} does not have positive area", i);
			return 0;
		}
		if !(out[i].x1 <= input.ps[i].0 && input.ps[i].0 < out[i].x2 && out[i].y1 <= input.ps[i].1 && input.ps[i].1 < out[i].y2) {
			eprintln!("rectangle {} does not contain point {}", i, i);
			continue;
		}
		for j in 0..i {
			if intersect(&out[i], &out[j]) {
				eprintln!("rectangles {} and {} overlap", j, i);
				return 0;
			}
		}
		let s = out[i].size().min(input.size[i]) as f64 / out[i].size().max(input.size[i]) as f64;
		score += 1.0 - (1.0 - s) * (1.0 - s);
	}
	(1e9 * score / n as f64).round() as i64
}

fn read_input(f: &str) -> Input {
	let f = std::fs::File::open(f).unwrap_or_else(|_| { eprintln!("no such file: {}", f); std::process::exit(1) });
	let f = line::LineSource::new(std::io::BufReader::new(f));
	input! {
		from f,
		n: usize,
		xys: [(i64, i64, i64); n]
	}
	let ps = xys.iter().map(|&(x, y, _)| (x, y)).collect::<Vec<_>>();
	let size = xys.iter().map(|&(_, _, s)| s).collect::<Vec<_>>();
	Input { ps, size }
}

fn read_output(input: &Input, f: &str) -> Vec<Rect> {
	let f = std::fs::File::open(f).unwrap_or_else(|_| { eprintln!("no such file: {}", f); std::process::exit(1) });
	let f = line::LineSource::new(std::io::BufReader::new(f));
	input! {
		from f,
		xyxy: [(i64, i64, i64, i64); input.ps.len()]
	}
	xyxy.into_iter().map(|(x1, y1, x2, y2)| Rect { x1, y1, x2, y2 }).collect()
}

use svg::node::element::{Path, path::Data};

fn rect(r: Rect) -> Data {
	Data::new().move_to((r.x1, r.y1)).line_by((r.x2 - r.x1, 0)).line_by((0, r.y2 - r.y1)).line_by((r.x1 - r.x2, 0)).close()
}

// 0 <= val <= 1
fn color(val: f64) -> String {
	let tmp = ((-(2.0 * std::f64::consts::PI * val).cos() / 2.0 + 0.5) * 255.0) as i32;
	if val >= 0.5 {
		format!("#{:02x}{:02x}{:02x}", 255, 0, tmp)
	} else {
		format!("#{:02x}{:02x}{:02x}", tmp, 0, 255)
	}
}

fn vis(input: &Input, out: &Vec<Rect>, show_id: bool) {
	let mut doc = svg::Document::new().set("viewBox", (0, 0, W, W));
	doc = doc.add(Path::new().set("fill", "white").set("d", rect(Rect { x1: 0, y1: 0, x2: W, y2: W })));
	for i in 0..input.ps.len() {
		let val = if out[i].size() > input.size[i] {
			1.0 - input.size[i] as f64 / out[i].size() as f64 / 2.0
		} else {
			out[i].size() as f64 / input.size[i] as f64 / 2.0
		};
		let path = Path::new().set("fill", color(val)).set("stroke", "black").set("stroke-width", 5.0).set("d", rect(out[i]));
		doc = doc.add(path);
	}
	for i in 0..input.ps.len() {
		let data = rect(Rect { x1: input.ps[i].0 - 30, x2: input.ps[i].0 + 30, y1: input.ps[i].1 - 30, y2: input.ps[i].1 + 30 });
		let path = Path::new().set("fill", "green").set("d", data);
		doc = doc.add(path);
		let cx = (out[i].x1 + out[i].x2) as f64 / 2.0;
		let cy = (out[i].y1 + out[i].y2) as f64 / 2.0;
		let data = Data::new().move_to(input.ps[i]).line_by((cx - input.ps[i].0 as f64, cy - input.ps[i].1 as f64));
		let path = Path::new().set("stroke", "black").set("stroke-width", 5.0).set("d", data);
		doc = doc.add(path);
	}
	if show_id {
		let fontsize = 200.0 / (input.ps.len() as f64 / 50.0).sqrt();
		for i in 0..input.ps.len() {
			let cx = (out[i].x1 + out[i].x2) as f64 / 2.0;
			let cy = (out[i].y1 + out[i].y2) as f64 / 2.0;
			doc = doc.add(svg::node::element::Text::new().set("x", cx).set("y", cy + fontsize * 0.35).set("font-size", fontsize).set("text-anchor", "middle").add(svg::node::Text::new(format!("{}", i))));
		}
	}
	svg::save("out.svg", &doc).unwrap();
}

fn main() {
	if std::env::args().len() != 3 {
		eprintln!("Usage: {} <input> <output>", std::env::args().nth(0).unwrap());
		return;
	}
	let input = read_input(&std::env::args().nth(1).unwrap());
	let output = read_output(&input, &std::env::args().nth(2).unwrap());
	println!("{}", score(&input, &output));
	vis(&input, &output, true);
}
