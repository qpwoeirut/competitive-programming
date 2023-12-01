#![allow(non_snake_case, unused_macros)]

use itertools::Itertools;
use proconio::input;
use rand::prelude::*;
use std::{io::prelude::*, io::BufReader, process::ChildStdout};
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
    pub N: usize,
    pub D: usize,
    pub Q: usize,
    pub ws: Vec<i64>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {}", self.N, self.D, self.Q)?;
        writeln!(f, "{}", self.ws.iter().join(" "))?;
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        N: usize, D: usize, Q: usize,
        ws: [i64; N]
    }
    Input { N, D, Q, ws }
}

pub fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr>(
    token: Option<&str>,
    lb: T,
    ub: T,
) -> Result<T, String> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            if v < lb || ub < v {
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
    pub outs: Vec<Vec<usize>>,
    pub query: Vec<(Vec<usize>, Vec<usize>)>,
    pub comments: Vec<String>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut comments = vec![];
    let mut comment = String::new();
    let mut query = vec![];
    let mut outs = vec![];
    let mut out = vec![];
    for line in f.lines() {
        let line = line.trim();
        if line.len() == 0 {
            continue;
        } else if line.starts_with("#c ") {
            out.clear();
            let mut tokens = line.trim_start_matches("#c ").trim().split_whitespace();
            for _ in 0..input.N {
                let i = read(tokens.next(), -1, input.D as i32 - 1)?;
                out.push(i as usize);
            }
            if tokens.next().is_some() {
                return Err(format!("Too many output: {}", line));
            }
        } else if line.starts_with('#') {
            let line = line.trim_start_matches('#').trim();
            comment += line;
            comment.push('\n');
        } else if query.len() == input.Q {
            out.clear();
            let mut tokens = line.split_whitespace();
            for _ in 0..input.N {
                out.push(read(tokens.next(), 0, input.D - 1)?);
            }
            if tokens.next().is_some() {
                return Err(format!("Too many output: {}", line));
            }
            comments.push(comment);
            outs.push(out);
            break;
        } else {
            let mut tokens = line.split_whitespace();
            let n1 = read(tokens.next(), 1, input.N)?;
            let n2 = read(tokens.next(), 1, input.N)?;
            let mut used = vec![false; input.N];
            let mut is1 = vec![];
            let mut is2 = vec![];
            for _ in 0..n1 {
                let i = read(tokens.next(), 0, input.N - 1)?;
                if !used[i].setmax(true) {
                    return Err(format!("Item {} appears multiple times.", i));
                }
                is1.push(i);
            }
            for _ in 0..n2 {
                let i = read(tokens.next(), 0, input.N - 1)?;
                if !used[i].setmax(true) {
                    return Err(format!("Item {} appears multiple times.", i));
                }
                is2.push(i);
            }
            query.push((is1, is2));
            if tokens.next().is_some() {
                return Err(format!("Illegal output format: {}", line));
            }
            comments.push(comment);
            comment = String::new();
            outs.push(out.clone());
        }
    }
    if outs.len() <= input.Q {
        return Err("Unexpected EOF".to_owned());
    }
    Ok(Output { outs, query, comments })
}

pub fn gen(seed: u64, fixN: Option<usize>, fixD: Option<usize>, fixQ: Option<usize>) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed ^ 94);
    let mut N = rng.gen_range(30i32..=100) as usize;
    if let Some(fixN) = fixN {
        N = fixN;
    }
    let mut D = rng.gen_range(2..=N as i32 / 4) as usize;
    if let Some(fixD) = fixD {
        D = fixD;
    }
    let mut Q = (N as f64 * f64::powf(2.0, rng.gen_range(1.0..5.0))).round() as usize;
    if let Some(fixQ) = fixQ {
        Q = fixQ;
    }
    let mut ws = vec![];
    let exp = rand_distr::Exp::new(1e-5).unwrap();
    for _ in 0..N {
        loop {
            let w = rng.sample(exp);
            if w <= N as f64 * 1e5 / D as f64 {
                ws.push((f64::round(w) as i64).max(1));
                break;
            }
        }
    }
    Input { N, D, Q, ws }
}

pub fn compute_score(input: &Input, out: &[usize]) -> (i64, String) {
    let (mut score, err, _) = compute_score_details(input, &out);
    if err.len() > 0 {
        score = 0;
    }
    (score, err)
}

pub fn compute_score_details(input: &Input, out: &[usize]) -> (i64, String, ()) {
    if out.len() == 0 {
        return (0, "empty output".to_owned(), ());
    }
    let mut sum = vec![0; input.D];
    let mut avg = 0;
    for i in 0..input.N {
        if out[i] == !0 {
            continue;
        }
        sum[out[i]] += input.ws[i];
        avg += input.ws[i];
    }
    let mut sum2 = 0;
    for i in 0..input.D {
        sum2 += sum[i] * sum[i];
    }
    let score = 1 + (((sum2 * input.D as i64 - avg * avg) as f64).sqrt() / input.D as f64 * 100.0).round() as i64;
    (score, String::new(), ())
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
    let (mut score, err, svg) = vis(input, &out, input.Q);
    if err.len() > 0 {
        score = 0;
    }
    (score, err, svg)
}

pub fn vis(input: &Input, output: &Output, t: usize) -> (i64, String, String) {
    let W = 600usize;
    let H = 600usize;
    let out = &output.outs[t];
    let (score, err, _) = compute_score_details(input, &out);
    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (-5, -5, W + 10, H + 10))
        .set("width", W + 10)
        .set("height", H + 10)
        .set("style", "background-color:white");
    doc = doc.add(Style::new(format!(
        "text {{text-anchor: middle;dominant-baseline: central;}}
        .vis_item:hover rect {{stroke-width: 3}}"
    )));
    let mut groups = vec![];
    for i in 0..input.N {
        groups.push(group(format!("w[{}] = {}", i, input.ws[i])).set("class", "vis_item"));
    }
    if t < input.Q {
        let mut sum1 = 0;
        let mut sum2 = 0;
        for &i in &output.query[t].0 {
            sum1 += input.ws[i];
        }
        for &i in &output.query[t].1 {
            sum2 += input.ws[i];
        }
        let max = sum1.max(sum2);
        sum1 = 0;
        sum2 = 0;
        for &i in &output.query[t].0 {
            groups[i] = groups[i].clone().add(
                rect(
                    (sum1 * W as i64 / max) as usize,
                    0,
                    ((sum1 + input.ws[i]) * W as i64 / max - sum1 * W as i64 / max) as usize,
                    60,
                    &color(1.0 - (-input.ws[i] as f64 / 1e5).exp()),
                )
                .set("stroke", "black")
                .set("stroke-width", 1),
            );
            sum1 += input.ws[i];
        }
        for &i in &output.query[t].1 {
            groups[i] = groups[i].clone().add(
                rect(
                    (sum2 * W as i64 / max) as usize,
                    120,
                    ((sum2 + input.ws[i]) * W as i64 / max - sum2 * W as i64 / max) as usize,
                    60,
                    &color(1.0 - (-input.ws[i] as f64 / 1e5).exp()),
                )
                .set("stroke", "black")
                .set("stroke-width", 1),
            );
            sum2 += input.ws[i];
        }
        doc = doc.add(
            svg::node::element::Text::new()
                .add(Text::new(if sum1 < sum2 {
                    "<"
                } else if sum1 > sum2 {
                    ">"
                } else {
                    "="
                }))
                .set("x", W / 2)
                .set("y", 90)
                .set("transform", format!("rotate(90,{},{})", W / 2, 90))
                .set("fill", "black")
                .set("font-size", 60),
        )
    }
    if out.len() > 0 {
        let mut sum = vec![0; input.D];
        let mut set = vec![vec![]; input.D];
        for i in 0..input.N {
            if out[i] == !0 {
                continue;
            }
            set[out[i]].push(i);
            sum[out[i]] += input.ws[i];
        }
        let mut max = 0;
        for i in 0..input.D {
            max.setmax(sum[i]);
            sum[i] = 0;
        }
        for i in 0..input.N {
            if out[i] == !0 {
                continue;
            }
            groups[i] = groups[i].clone().add(
                rect(
                    out[i] * W / input.D + 2,
                    H - ((sum[out[i]] + input.ws[i]) * 400 / max) as usize,
                    (out[i] + 1) * W / input.D - out[i] * W / input.D - 4,
                    ((sum[out[i]] + input.ws[i]) * 400 / max - sum[out[i]] * 400 / max) as usize,
                    &color(1.0 - (-input.ws[i] as f64 / 1e5).exp()),
                )
                .set("stroke", "black")
                .set("stroke-width", 1),
            );
            sum[out[i]] += input.ws[i];
        }
        let avg = sum.iter().sum::<i64>() as usize / input.D;
        doc = doc.add(
            Line::new()
                .set("x1", 0)
                .set("y1", H - avg * 400 / max as usize)
                .set("x2", W)
                .set("y2", H - avg * 400 / max as usize)
                .set("stroke", "pink")
                .set("stroke-width", 2),
        );
    }
    for g in groups {
        doc = doc.add(g);
    }
    (score, err, doc.to_string())
}

fn read_line(stdout: &mut BufReader<ChildStdout>, local: bool) -> Result<String, String> {
    loop {
        let mut out = String::new();
        match stdout.read_line(&mut out) {
            Ok(0) | Err(_) => {
                return Err(format!("Your program has terminated unexpectedly"));
            }
            _ => (),
        }
        if local {
            print!("{}", out);
        }
        let v = out.trim();
        if v.len() == 0 || v.starts_with("#") {
            continue;
        }
        return Ok(v.to_owned());
    }
}

pub fn exec(p: &mut std::process::Child, local: bool) -> Result<i64, String> {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = parse_input(&input);
    let mut stdin = std::io::BufWriter::new(p.stdin.take().unwrap());
    let mut stdout = std::io::BufReader::new(p.stdout.take().unwrap());
    let _ = writeln!(stdin, "{} {} {}", input.N, input.D, input.Q);
    let _ = stdin.flush();
    for _ in 0..input.Q {
        let line = read_line(&mut stdout, local)?;
        let mut tokens = line.split_whitespace();
        let n1 = read(tokens.next(), 1, input.N)?;
        let n2 = read(tokens.next(), 1, input.N)?;
        let mut used = vec![false; input.N];
        let mut is1 = vec![];
        let mut is2 = vec![];
        for _ in 0..n1 {
            let i = read(tokens.next(), 0, input.N - 1)?;
            if !used[i].setmax(true) {
                return Err(format!("Item {} appears multiple times.", i));
            }
            is1.push(i);
        }
        for _ in 0..n2 {
            let i = read(tokens.next(), 0, input.N - 1)?;
            if !used[i].setmax(true) {
                return Err(format!("Item {} appears multiple times.", i));
            }
            is2.push(i);
        }
        if tokens.next().is_some() {
            return Err(format!("Illegal output format: {}", line));
        }
        let mut sum1 = 0;
        let mut sum2 = 0;
        for i in is1 {
            sum1 += input.ws[i];
        }
        for i in is2 {
            sum2 += input.ws[i];
        }
        if sum1 < sum2 {
            let _ = writeln!(stdin, "<");
        } else if sum1 > sum2 {
            let _ = writeln!(stdin, ">");
        } else {
            let _ = writeln!(stdin, "=");
        }
        let _ = stdin.flush();
    }
    let mut out = vec![];
    let line = read_line(&mut stdout, local)?;
    let mut tokens = line.split_whitespace();
    for _ in 0..input.N {
        out.push(read(tokens.next(), 0, input.D - 1)?);
    }
    if tokens.next().is_some() {
        return Err(format!("Too many output: {}", line));
    }
    p.wait().unwrap();
    Ok(compute_score(&input, &out).0)
}
