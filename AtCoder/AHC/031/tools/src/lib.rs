#![allow(non_snake_case, unused_macros)]

use itertools::Itertools;
use proconio::input;
use rand::prelude::*;
use std::{collections::BTreeSet, ops::RangeBounds};
use svg::node::{
    element::{Group, Line, Rectangle, Style, Title},
    Text,
};

pub trait SetMinMax {
    fn setmin(&mut self, v: Self) -> bool;
    fn setmax(&mut self, v: Self) -> bool;
}
impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin(&mut self, v: T) -> bool {
        *self > v && {
            *self = v;
            true
        }
    }
    fn setmax(&mut self, v: T) -> bool {
        *self < v && {
            *self = v;
            true
        }
    }
}

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

#[derive(Clone, Debug)]
pub struct Input {
    pub W: usize,
    pub D: usize,
    pub N: usize,
    pub a: Vec<Vec<usize>>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {}", self.W, self.D, self.N)?;
        for i in 0..self.D {
            writeln!(f, "{}", self.a[i].iter().join(" "))?;
        }
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        W: usize, D: usize, N: usize,
        a: [[usize; N]; D],
    }
    Input { W, D, N, a }
}

pub fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr, R: RangeBounds<T>>(
    token: Option<&str>,
    range: R,
) -> Result<T, String> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            if !range.contains(&v) {
                Err(format!("Out of range: {}", v))
            } else {
                Ok(v)
            }
        } else {
            Err(format!("Parse error: {}", v))
        }
    } else {
        Err("Unexpected EOF".to_owned())
    }
}

pub struct Output {
    pub out: Vec<Vec<(usize, usize, usize, usize)>>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut out = mat![(0, 0, 0, 0); input.D; input.N];
    let mut ss = f.split_whitespace();
    for d in 0..input.D {
        for i in 0..input.N {
            let i0 = read(ss.next(), 0..=input.W)?;
            let j0 = read(ss.next(), 0..=input.W)?;
            let i1 = read(ss.next(), 0..=input.W)?;
            let j1 = read(ss.next(), 0..=input.W)?;
            if i0 >= i1 || j0 >= j1 {
                return Err(format!(
                    "Invalid rectangle: {} {} {} {} (d = {}, k = {})",
                    i0, j0, i1, j1, d, i
                ));
            }
            out[d][i] = (i0, j0, i1, j1);
        }
    }
    if ss.next().is_some() {
        return Err("Too many output".to_owned());
    }
    Ok(Output { out })
}

pub fn gen(seed: u64, fix_D: Option<usize>, fix_N: Option<usize>, fix_E: Option<usize>) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed ^ 677);
    let W = 1000;
    let mut D = rng.gen_range(5i32..=50) as usize;
    if let Some(fix_D) = fix_D {
        D = fix_D;
    }
    let mut N = rng.gen_range(5i32..=50) as usize;
    if let Some(fix_N) = fix_N {
        N = fix_N;
    }
    let e = rng.gen_range(500..=5000) as f64 / 10000.0;
    let mut E = ((W * W) as f64 * e * e).round() as usize;
    if let Some(fix_E) = fix_E {
        E = fix_E;
    }
    let mut a = vec![vec![]; D];
    for d in 0..D {
        let total = rng.gen_range((W * W - E * 3 / 2) as i32..=(W * W - E / 2) as i32);
        let mut set = std::collections::BTreeSet::new();
        set.insert(0);
        set.insert(total);
        while set.len() <= N {
            set.insert(rng.gen_range(1..total));
        }
        let set = set.into_iter().collect::<Vec<_>>();
        for i in 0..N {
            a[d].push((set[i + 1] - set[i]) as usize);
        }
        a[d].sort();
    }
    Input { W, D, N, a }
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String) {
    let (mut score, err, _) = compute_score_details(input, &out.out);
    if err.len() > 0 {
        score = 0;
    }
    (score, err)
}

pub fn compute_score_details(
    input: &Input,
    out: &[Vec<(usize, usize, usize, usize)>],
) -> (i64, String, Vec<(usize, usize, usize, usize, bool)>) {
    let mut score = 0;
    let mut change: Vec<(usize, usize, usize, usize, bool)> = vec![];
    let mut hs = BTreeSet::new();
    let mut vs = BTreeSet::new();
    for d in 0..out.len() {
        for p in 0..input.N {
            for q in 0..p {
                if out[d][p].2.min(out[d][q].2) > out[d][p].0.max(out[d][q].0)
                    && out[d][p].3.min(out[d][q].3) > out[d][p].1.max(out[d][q].1)
                {
                    return (0, format!("Rectangles {} and {} overlap on day {}.", q, p, d), vec![]);
                }
            }
        }
        let mut hs2 = BTreeSet::new();
        let mut vs2 = BTreeSet::new();
        for k in 0..input.N {
            let (i0, j0, i1, j1) = out[d][k];
            let b = (i1 - i0) * (j1 - j0);
            if input.a[d][k] > b {
                score += 100 * (input.a[d][k] - b) as i64;
            }
            for j in j0..j1 {
                if i0 > 0 {
                    hs2.insert((i0, j));
                }
                if i1 < input.W {
                    hs2.insert((i1, j));
                }
            }
            for i in i0..i1 {
                if j0 > 0 {
                    vs2.insert((j0, i));
                }
                if j1 < input.W {
                    vs2.insert((j1, i));
                }
            }
        }
        if d > 0 {
            for &(i, j) in &hs {
                if !hs2.contains(&(i, j)) {
                    score += 1;
                    if d + 1 == out.len() {
                        if change.len() > 0 && change[change.len() - 1] == (i, change[change.len() - 1].1, i, j, false) {
                            change.last_mut().unwrap().3 += 1;
                        } else {
                            change.push((i, j, i, j + 1, false));
                        }
                    }
                }
            }
            for &(j, i) in &vs {
                if !vs2.contains(&(j, i)) {
                    score += 1;
                    if d + 1 == out.len() {
                        if change.len() > 0 && change[change.len() - 1] == (change[change.len() - 1].0, j, i, j, false) {
                            change.last_mut().unwrap().2 += 1;
                        } else {
                            change.push((i, j, i + 1, j, false));
                        }
                    }
                }
            }
            for &(i, j) in &hs2 {
                if !hs.contains(&(i, j)) {
                    score += 1;
                    if d + 1 == out.len() {
                        if change.len() > 0 && change[change.len() - 1] == (i, change[change.len() - 1].1, i, j, true) {
                            change.last_mut().unwrap().3 += 1;
                        } else {
                            change.push((i, j, i, j + 1, true));
                        }
                    }
                }
            }
            for &(j, i) in &vs2 {
                if !vs.contains(&(j, i)) {
                    score += 1;
                    if d + 1 == out.len() {
                        if change.len() > 0 && change[change.len() - 1] == (change[change.len() - 1].0, j, i, j, true) {
                            change.last_mut().unwrap().2 += 1;
                        } else {
                            change.push((i, j, i + 1, j, true));
                        }
                    }
                }
            }
        }
        hs = hs2;
        vs = vs2;
    }
    (score + 1, String::new(), change)
}

/// 0 <= val <= 1
pub fn color(mut val: f64) -> String {
    val.setmin(1.0);
    val.setmax(0.0);
    let (r, g, b) = if val < 0.5 {
        let x = val * 2.0;
        (
            30. * (1.0 - x) + 144. * x,
            144. * (1.0 - x) + 255. * x,
            255. * (1.0 - x) + 30. * x,
        )
    } else {
        let x = val * 2.0 - 1.0;
        (
            144. * (1.0 - x) + 255. * x,
            255. * (1.0 - x) + 30. * x,
            30. * (1.0 - x) + 70. * x,
        )
    };
    format!("#{:02x}{:02x}{:02x}", r.round() as i32, g.round() as i32, b.round() as i32)
}

pub fn rect(x: usize, y: usize, w: usize, h: usize, fill: &str) -> Rectangle {
    Rectangle::new()
        .set("x", x)
        .set("y", y)
        .set("width", w)
        .set("height", h)
        .set("fill", fill)
}

pub fn group(title: String) -> Group {
    Group::new().add(Title::new().add(Text::new(title)))
}

pub fn vis_default(input: &Input, out: &Output) -> (i64, String, String) {
    let (mut score, err, svg) = vis(input, &out.out);
    if err.len() > 0 {
        score = 0;
    }
    (score, err, svg)
}

pub fn vis(input: &Input, out: &[Vec<(usize, usize, usize, usize)>]) -> (i64, String, String) {
    let (score, err, change) = compute_score_details(input, out);
    let W = input.W;
    let H = input.W;
    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (-5, -5, W + 10, H + 10))
        .set("width", W + 10)
        .set("height", H + 10)
        .set("style", "background-color:white");
    doc = doc.add(Style::new(format!(
        "text {{text-anchor: middle;dominant-baseline: central;}}
        #vis rect.rect:hover {{
            stroke-width: 5;
        }}"
    )));
    doc = doc.add(rect(0, 0, W, H, "none").set("stroke", "black"));
    if out.len() > 0 {
        for k in 0..input.N {
            let R = out[out.len() - 1][k];
            let b = (R.2 - R.0) * (R.3 - R.1);
            doc = doc.add(
                group(format!(
                    "R[{},{}] = ({}, {}, {}, {})\na = {}, b = {}",
                    out.len() - 1,
                    k,
                    R.0,
                    R.1,
                    R.2,
                    R.3,
                    input.a[out.len() - 1][k],
                    b
                ))
                .add(
                    rect(
                        R.1,
                        R.0,
                        R.3 - R.1,
                        R.2 - R.0,
                        &if input.a[out.len() - 1][k] > b {
                            format!("#ff0000{:02x}", ((input.a[out.len() - 1][k] - b) * 5).min(255))
                        } else {
                            "white".to_owned()
                        },
                    )
                    .set("stroke", "black")
                    .set("stroke-width", 2)
                    .set("class", "rect"),
                ),
            );
        }
        for (i0, j0, i1, j1, add) in change {
            let mut line = Line::new()
                .set("x1", j0)
                .set("y1", i0)
                .set("x2", j1)
                .set("y2", i1)
                .set("stroke", "blue")
                .set("stroke-width", 3);
            if !add {
                line = line.set("stroke-dasharray", 3);
            }
            doc = doc.add(line);
        }
    }
    (score, err, doc.to_string())
}
