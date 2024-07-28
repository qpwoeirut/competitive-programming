#![allow(non_snake_case, unused_macros)]
use itertools::Itertools;
use proconio::{input, marker::Chars};
use rand::prelude::*;
use rand_distr::StandardNormal;
use std::collections::HashSet;
use std::io::{BufRead, BufReader, Read, Write};
use std::process::ChildStdout;
use svg::node;
use svg::node::element::path::Data;
use svg::node::element::{Path, SVG};
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

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Input {
    pub n: usize,
    pub m: usize,
    pub t: usize,
    pub x: Vec<Vec<u32>>,
    pub u: Vec<Vec<Vec<Vec<char>>>>,
    pub v: Vec<Vec<Vec<Vec<char>>>>,
}

impl Input {
    pub fn new(
        n: usize,
        m: usize,
        t: usize,
        x: Vec<Vec<u32>>,
        u: Vec<Vec<Vec<Vec<char>>>>,
        v: Vec<Vec<Vec<Vec<char>>>>,
    ) -> Self {
        Self { n, m, t, x, u, v }
    }

    fn seed_count(&self) -> usize {
        2 * self.n * (self.n - 1)
    }

    fn calc_ideal(&self) -> Vec<u32> {
        let mut ideal = vec![0; self.m];

        for x in self.x.iter() {
            for i in 0..self.m {
                ideal[i].setmax(x[i]);
            }
        }

        ideal
    }
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {}", self.n, self.m, self.t)?;

        for i in 0..self.seed_count() {
            let s = self.x[i].iter().map(|x| x.to_string()).join(" ");

            writeln!(f, "{}", s)?;
        }

        for t in 0..self.t {
            for i in 0..self.n {
                let u = self.u[t][i]
                    .iter()
                    .map(|v| v.iter().collect::<String>())
                    .join(" ");

                writeln!(f, "{}", u)?;
            }

            for i in 0..self.n - 1 {
                let v = self.v[t][i]
                    .iter()
                    .map(|v| v.iter().collect::<String>())
                    .join(" ");

                writeln!(f, "{}", v)?;
            }
        }

        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let mut f = proconio::source::once::OnceSource::from(f);
    input! {
        from &mut f,
        n: usize,
        m: usize,
        t: usize,
        x: [[u32; m]; 2 * n * (n - 1)],
    }

    let mut u = vec![];
    let mut v = vec![];

    for _ in 0..t {
        input! {
            from &mut f,
            uu: [[Chars; n - 1]; n],
        }

        input! {
            from &mut f,
            vv: [[Chars; n]; n - 1],
        }

        u.push(uu);
        v.push(vv);
    }

    Input { n, m, t, x, u, v }
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

#[derive(Debug, Clone)]
pub struct Sim {
    pub a: Vec<Vec<Vec<usize>>>,
    pub x: Vec<Vec<Vec<u32>>>,
    pub turn: usize,
}

impl Sim {
    fn new(input: &Input) -> Self {
        Self {
            a: vec![],
            x: vec![input.x.clone()],
            turn: 0,
        }
    }

    fn query(&mut self, input: &Input, a: Vec<Vec<usize>>) {
        let x = self.x.last().unwrap();
        let mut new_x = vec![];

        for i in 0..input.n {
            for j in 0..input.n - 1 {
                let mut xx = vec![];

                for k in 0..input.m {
                    if input.u[self.turn][i][j][k] == '0' {
                        xx.push(x[a[i][j]][k]);
                    } else {
                        xx.push(x[a[i][j + 1]][k]);
                    }
                }

                new_x.push(xx);
            }
        }

        for i in 0..input.n - 1 {
            for j in 0..input.n {
                let mut xx = vec![];

                for k in 0..input.m {
                    if input.v[self.turn][i][j][k] == '0' {
                        xx.push(x[a[i][j]][k]);
                    } else {
                        xx.push(x[a[i + 1][j]][k]);
                    }
                }

                new_x.push(xx);
            }
        }

        self.a.push(a);
        self.x.push(new_x);
        self.turn += 1;
    }
}

#[derive(Debug, Clone)]
pub struct Output {
    pub sim: Sim,
    pub comments: Vec<String>,
}

impl Output {
    pub fn new(sim: Sim, comments: Vec<String>) -> Self {
        Self { sim, comments }
    }
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut lines = f.lines();
    let mut sim = Sim::new(input);
    let mut comments = vec![];

    while sim.turn < input.t {
        if let Err(msg) = proceed(input, &mut lines, &mut sim, &mut comments) {
            return Err(format!("{} (Turn {})", msg, sim.turn));
        }
    }

    Ok(Output::new(sim, comments))
}

fn proceed(
    input: &Input,
    lines: &mut std::str::Lines,
    sim: &mut Sim,
    comments: &mut Vec<String>,
) -> Result<(), String> {
    let mut a = vec![];
    let mut comment = String::new();
    let mut set = HashSet::new();
    let mut line_i = 0;

    while line_i < input.n {
        let Some(line) = lines.next() else {
            return Err("Unexpected EOF".to_owned());
        };

        let line = line.trim();
        if line.starts_with("#") {
            let line = line.trim_start_matches('#').trim();
            comment += line;
            comment.push('\n');
            continue;
        } else if line.is_empty() {
            continue;
        }

        let mut s = line.split_whitespace();
        let mut aa = vec![];

        for _ in 0..input.n {
            let Some(v) = s.next() else {
                return Err(format!("Invalid query format: {}", line));
            };

            let v = read(Some(v), 0, input.seed_count() - 1)?;

            if set.insert(v) {
                aa.push(v);
            } else {
                return Err(format!("Seed {} is used multiple times", v));
            }
        }

        a.push(aa);
        line_i += 1;

        if s.next().is_some() {
            return Err(format!("Invalid query format: {}", line));
        }
    }

    sim.query(&input, a);

    comments.push(comment);

    Ok(())
}

const MAX_V: f64 = 100.0;

pub fn gen(seed: u64) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
    let n = 6;
    let m = 15;
    let t = 10;
    let mut x = vec![];
    let dist = StandardNormal;

    for _ in 0..2 * n * (n - 1) {
        let xx = (0..m)
            .map(|_| f64::abs(dist.sample(&mut rng)))
            .collect_vec();

        let p = 100.0 / xx.iter().map(|x| x * x).sum::<f64>().sqrt();
        let xx = xx.iter().map(|x| (x * p).round() as u32).collect_vec();

        x.push(xx);
    }

    let mut u = vec![];
    let mut v = vec![];

    for _ in 0..t {
        let uu = (0..n)
            .map(|_| {
                (0..n - 1)
                    .map(|_| {
                        (0..m)
                            .map(|_| if rng.gen_bool(0.5) { '1' } else { '0' })
                            .collect_vec()
                    })
                    .collect_vec()
            })
            .collect_vec();

        u.push(uu);

        let vv = (0..n - 1)
            .map(|_| {
                (0..n)
                    .map(|_| {
                        (0..m)
                            .map(|_| if rng.gen_bool(0.5) { '1' } else { '0' })
                            .collect_vec()
                    })
                    .collect_vec()
            })
            .collect_vec();

        v.push(vv);
    }

    Input::new(n, m, t, x, u, v)
}

pub fn compute_score(input: &Input, out: &Output, t: usize) -> Result<i64, String> {
    compute_score_details(input, out, t)
}

pub fn compute_score_details(input: &Input, out: &Output, t: usize) -> Result<i64, String> {
    let x = &out.sim.x[t];

    let mut sum = 0;

    for x in x.iter() {
        let s = x.iter().map(|&x| x as i64).sum::<i64>();
        sum.setmax(s);
    }

    let ideal = input.calc_ideal();
    let ideal = ideal.iter().map(|&x| x as i64).sum::<i64>();
    let score = (sum as f64 / ideal as f64 * 1e6).round() as i64;

    Ok(score)
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
    format!(
        "#{:02x}{:02x}{:02x}",
        r.round() as i32,
        g.round() as i32,
        b.round() as i32
    )
}

pub fn line(
    x1: impl Into<node::Value>,
    y1: impl Into<node::Value>,
    x2: impl Into<node::Value>,
    y2: impl Into<node::Value>,
    stroke: impl Into<node::Value>,
    stroke_width: impl Into<node::Value>,
) -> Line {
    Line::new()
        .set("x1", x1)
        .set("y1", y1)
        .set("x2", x2)
        .set("y2", y2)
        .set("stroke", stroke)
        .set("stroke-width", stroke_width)
}

pub fn rect(
    x: impl Into<node::Value>,
    y: impl Into<node::Value>,
    w: impl Into<node::Value>,
    h: impl Into<node::Value>,
    fill: impl Into<node::Value>,
) -> Rectangle {
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

pub struct VisResult {
    pub score: i64,
    pub svg: String,
    pub comment: String,
}

impl VisResult {
    pub fn new(score: i64, svg: String, comment: String) -> Self {
        Self {
            score,
            svg,
            comment,
        }
    }
}

pub fn vis_default(input: &Input, out: &Output) -> Result<VisResult, String> {
    vis(input, &out, input.t, false, -1)
}

pub fn vis_init(input: &Input, color: i32) -> Result<VisResult, String> {
    let sim = Sim::new(input);
    let comments = vec![String::new(); input.t];
    let out = Output::new(sim, comments);
    vis(input, &out, 0, false, color)
}

pub fn vis(
    input: &Input,
    out: &Output,
    t: usize,
    planted: bool,
    color: i32,
) -> Result<VisResult, String> {
    const W: f64 = 1180.0;
    const H: f64 = 510.0;

    let score = compute_score(input, &out, t)?;

    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (0, 0, W, H))
        .set("width", W)
        .set("height", H)
        .set("style", "background-color:white");

    doc = doc.add(Style::new(format!(
        "text {{text-anchor: middle;dominant-baseline: central;}}"
    )));

    doc = doc.add(vis_stock(input, planted, out, t, color));
    doc = doc.add(
        vis_plant(input, planted, t, out, color)
            .set("x", 690)
            .set("y", 0),
    );
    if t > 0 || planted {
        doc = doc.add(
            svg::node::element::Text::new()
                .add(Text::new(if planted { "➡" } else { "⬅" }))
                .set("x", 660)
                .set("y", 240)
                .set("font-size", 50)
                .set("fill", "gray"),
        );
    }

    let comment_turn = if planted { t } else { t.wrapping_sub(1) };
    let comment = out
        .comments
        .get(comment_turn)
        .cloned()
        .unwrap_or(String::new());

    let result = VisResult::new(score, doc.to_string(), comment);

    Ok(result)
}

fn vis_stock(input: &Input, planted: bool, out: &Output, t: usize, color_index: i32) -> SVG {
    const H: f64 = 500.0;
    const W: f64 = 620.0;
    const PADDING: f64 = 5.0;
    const D: f64 = 60.0;

    let mut doc = svg::Document::new()
        .set(
            "viewBox",
            (-PADDING, -PADDING, W + PADDING * 2.0, H + PADDING * 2.0),
        )
        .set("width", W + PADDING * 2.0)
        .set("height", H + PADDING * 2.0);

    let ideal_value = input.calc_ideal();

    let seeds = &out.sim.x[t];

    for id in 0..input.seed_count() {
        let v = &seeds[id];
        let j = id % 10;
        let i = id / 10;
        let x = D * (j as f64 + 0.5) + 10.0;
        let y = D * (i as f64 + 0.5) + 10.0;
        let r = D * 0.45;
        let value = v.iter().sum::<u32>();

        let mut group = Group::new();
        let mut highlight = vec![format!("vis_s{}", id)];
        if planted {
            highlight.push(format!("vis_p{}", i * input.n + j));
        } else if t > 0 {
            if id < input.n * (input.n - 1) {
                let i2 = id / (input.n - 1);
                let j2 = id % (input.n - 1);
                highlight.push(format!("vis_p{}", i2 * input.n + j2));
                highlight.push(format!("vis_p{}", i2 * input.n + j2 + 1));
            } else {
                let id = id - input.n * (input.n - 1);
                let i2 = id / input.n;
                let j2 = id % input.n;
                highlight.push(format!("vis_p{}", i2 * input.n + j2));
                highlight.push(format!("vis_p{}", (i2 + 1) * input.n + j2));
            }
        }
        let highlight = highlight.into_iter().map(|s| format!("'{}'", s)).join(", ");
        group = group
            .set("onmouseenter", format!("highlight([{}], true)", highlight))
            .set("onmouseleave", format!("highlight([{}], false)", highlight))
            .add(
                rect(D * j as f64 + 10.0, D * i as f64 + 10.0, D, D, "white")
                    .set("id", format!("vis_s{}", id)),
            );
        group = group.add(draw_radar(x, y, r, v, &ideal_value, color_index));

        let mut title = format!("seed {}\nvalue={}\nvector={:?}", id, value, v);
        if !planted {
            if let Some(a) = out.sim.a.get(t - 1) {
                let (p1, p2) = if id < input.n * (input.n - 1) {
                    let i2 = id / (input.n - 1);
                    let j2 = id % (input.n - 1);
                    (i2 * input.n + j2, i2 * input.n + j2 + 1)
                } else {
                    let id = id - input.n * (input.n - 1);
                    let i2 = id / input.n;
                    let j2 = id % input.n;
                    (i2 * input.n + j2, (i2 + 1) * input.n + j2)
                };
                let v1 = &out.sim.x[t - 1][a[p1 / input.n][p1 % input.n]];
                let value1 = v1.iter().sum::<u32>();
                let v2 = &out.sim.x[t - 1][a[p2 / input.n][p2 % input.n]];
                let value2 = v2.iter().sum::<u32>();
                title += &format!(
                    "\nparent1:\n  value={value1}\n  vector={v1:?}\nparent2:\n  value={value2}\n  vector={v2:?}",
                );
            }
        }
        group = group.add(Title::new().add(Text::new(title)));

        doc = doc.add(group);
    }

    let r = rect(0, 0, W, H - 20.0, "none")
        .set("stroke", "black")
        .set("stroke-width", 1.5)
        .set("rx", 15)
        .set("ry", 15);

    doc = doc.add(r);

    doc = doc.add(
        svg::node::element::Text::new()
            .add(Text::new(if t == 0 {
                "Initial seeds".to_owned()
            } else {
                format!("Harvested at t = {}", t - 1)
            }))
            .set("x", W / 2.0)
            .set("y", H - 10.0)
            .set("font-size", 20),
    );

    doc
}

fn vis_plant(input: &Input, planted: bool, t: usize, out: &Output, color_index: i32) -> SVG {
    const H: f64 = 500.0;
    const W: f64 = 500.0;
    const PADDING: f64 = 5.0;
    const D: f64 = 80.0;

    let mut doc = svg::Document::new()
        .set(
            "viewBox",
            (-PADDING, -PADDING, W + PADDING * 2.0, H + PADDING * 2.0),
        )
        .set("width", W + PADDING * 2.0)
        .set("height", H + PADDING * 2.0);

    doc = doc.add(
        rect(0, 0, D * input.n as f64, D * input.n as f64, "none")
            .set("stroke", "black")
            .set("stroke-width", 1.5),
    );

    let ideal_value = input.calc_ideal();

    let t_planted = if planted { t } else { t.wrapping_sub(1) };

    if let Some(a) = out.sim.a.get(t_planted) {
        let seeds = &out.sim.x[t_planted];

        for i in 0..input.n {
            for j in 0..input.n {
                let y = D * (i as f64 + 0.5);
                let x = D * (j as f64 + 0.5);
                let r = D as f64 * 0.4;
                let id = a[i][j];
                let v = &seeds[id];
                let value = v.iter().sum::<u32>();

                let pid = if planted { id } else { i * input.n + j };
                let mut highlight = vec![format!("vis_p{}", pid)];
                if planted {
                    highlight.push(format!("vis_s{}", id));
                } else {
                    if j > 0 {
                        highlight.push(format!("vis_s{}", i * (input.n - 1) + j - 1));
                    }
                    if j + 1 < input.n {
                        highlight.push(format!("vis_s{}", i * (input.n - 1) + j));
                    }
                    if i > 0 {
                        highlight.push(format!(
                            "vis_s{}",
                            input.n * (input.n - 1) + (i - 1) * input.n + j
                        ));
                    }
                    if i + 1 < input.n {
                        highlight.push(format!(
                            "vis_s{}",
                            input.n * (input.n - 1) + i * input.n + j
                        ));
                    }
                }
                let highlight = highlight.into_iter().map(|s| format!("'{}'", s)).join(", ");
                let mut group = Group::new()
                    .set("onmouseenter", format!("highlight([{}], true)", highlight))
                    .set("onmouseleave", format!("highlight([{}], false)", highlight))
                    .add(
                        rect(D * j as f64, D * i as f64, D, D, "white")
                            .set("id", format!("vis_p{}", pid)),
                    );
                group = group.add(draw_radar(x, y, r, v, &ideal_value, color_index));

                let title = format!(
                    "({}, {})\nseed {}\nvalue={}\nvector={:?}",
                    i, j, id, value, v
                );
                group = group.add(Title::new().add(Text::new(title)));

                doc = doc.add(group);
            }
        }

        doc = doc.add(
            svg::node::element::Text::new()
                .add(Text::new(format!("Planted at t = {}", t_planted)))
                .set("x", W / 2.0)
                .set("y", H - 10.0)
                .set("font-size", 20),
        );
    }

    for i in 0..=input.n {
        let line_x = line(
            0.0,
            i as f64 * D,
            input.n as f64 * D,
            i as f64 * D,
            "black",
            1.5,
        );

        doc = doc.add(line_x);

        let line_y = line(
            i as f64 * D,
            0.0,
            i as f64 * D,
            input.n as f64 * D,
            "black",
            1.5,
        );

        doc = doc.add(line_y);
    }

    if !planted {
        if let Some(a) = out.sim.a.get(t_planted) {
            let seeds = &out.sim.x[t_planted];
            let harvest = &out.sim.x[t];
            for i in 0..input.n {
                for j in 0..input.n {
                    if i + 1 < input.n {
                        let line = Line::new()
                            .set("x1", D * j as f64)
                            .set("y1", D * (i + 1) as f64)
                            .set("x2", D * (j + 1) as f64)
                            .set("y2", D * (i + 1) as f64)
                            .set("stroke", "transparent")
                            .set("stroke-width", 6.0);
                        let child = input.n * (input.n - 1) + i * input.n + j;
                        let highlight = vec![
                            format!("vis_p{}", i * input.n + j),
                            format!("vis_p{}", (i + 1) * input.n + j),
                            format!("vis_s{}", child),
                        ];
                        let highlight =
                            highlight.into_iter().map(|s| format!("'{}'", s)).join(", ");
                        let mut group = Group::new()
                            .set("onmouseenter", format!("highlight([{}], true)", highlight))
                            .set("onmouseleave", format!("highlight([{}], false)", highlight));
                        group = group.add(line);
                        let v1 = &seeds[a[i][j]];
                        let value1 = v1.iter().sum::<u32>();
                        let v2 = &seeds[a[i + 1][j]];
                        let value2 = v2.iter().sum::<u32>();
                        let v3 = &harvest[child];
                        let value3 = v3.iter().sum::<u32>();
                        let title = format!("parent1:\n  value={value1}\n  vector={v1:?}\nparent2:\n  value={value2}\n  vector={v2:?}\nchild:\n  value={value3}\n  vector={v3:?}");
                        group = group.add(Title::new().add(Text::new(title)));
                        doc = doc.add(group);
                    }
                    if j + 1 < input.n {
                        let line = Line::new()
                            .set("x1", D * (j + 1) as f64)
                            .set("y1", D * i as f64)
                            .set("x2", D * (j + 1) as f64)
                            .set("y2", D * (i + 1) as f64)
                            .set("stroke", "transparent")
                            .set("stroke-width", 6.0);
                        let child = i * (input.n - 1) + j;
                        let highlight = vec![
                            format!("vis_p{}", i * input.n + j),
                            format!("vis_p{}", i * input.n + j + 1),
                            format!("vis_s{}", child),
                        ];
                        let highlight =
                            highlight.into_iter().map(|s| format!("'{}'", s)).join(", ");
                        let mut group = Group::new()
                            .set("onmouseenter", format!("highlight([{}], true)", highlight))
                            .set("onmouseleave", format!("highlight([{}], false)", highlight));
                        group = group.add(line);
                        let v1 = &seeds[a[i][j]];
                        let value1 = v1.iter().sum::<u32>();
                        let v2 = &seeds[a[i][j + 1]];
                        let value2 = v2.iter().sum::<u32>();
                        let v3 = &harvest[child];
                        let value3 = v3.iter().sum::<u32>();
                        let title = format!("parent1:\n  value={value1}\n  vector={v1:?}\nparent2:\n  value={value2}\n  vector={v2:?}\nchild:\n  value={value3}\n  vector={v3:?}");
                        group = group.add(Title::new().add(Text::new(title)));
                        doc = doc.add(group);
                    }
                }
            }
        }
    }

    doc
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

fn draw_radar(x: f64, y: f64, r: f64, v: &[u32], ideal: &[u32], color_index: i32) -> Group {
    let mut group = Group::new();

    let color_numerator = if color_index < 0 {
        v.iter().sum::<u32>()
    } else {
        v[color_index as usize]
    };

    let color_denominator = if color_index < 0 {
        ideal.iter().sum::<u32>()
    } else {
        ideal[color_index as usize]
    };

    let color = color(color_numerator as f64 / color_denominator as f64);

    for i in 0..v.len() {
        let theta = 2.0 * std::f64::consts::PI * i as f64 / v.len() as f64;
        let x2 = x + theta.sin() * r;
        let y2 = y - theta.cos() * r;

        group = group.add(
            Line::new()
                .set("x1", x)
                .set("y1", y)
                .set("x2", x2)
                .set("y2", y2)
                .set("stroke", "lightgray")
                .set("stroke-width", 1),
        );
    }

    let data = get_radar_point_data(x, y, r, ideal);

    group = group.add(
        Path::new()
            .set("stroke", "gray")
            .set("stroke-width", 2)
            .set("fill", "none")
            .set("d", data),
    );

    let data = get_radar_point_data(x, y, r, v);

    group = group.add(
        Path::new()
            .set("fill", color)
            .set("stroke", "none")
            .set("d", data),
    );

    group
}

fn get_radar_point_data(x: f64, y: f64, r: f64, v: &[u32]) -> Data {
    let mut data = Data::new();

    for (i, &vi) in v.iter().enumerate() {
        let r = vi as f64 / MAX_V * r;
        let theta = 2.0 * std::f64::consts::PI * i as f64 / v.len() as f64;
        let x = x + theta.sin() * r;
        let y = y - theta.cos() * r;

        if i == 0 {
            data = data.move_to((x, y));
        } else {
            data = data.line_to((x, y));
        }
    }

    data = data.close();
    data
}

pub fn exec(p: &mut std::process::Child, local: bool) -> Result<i64, String> {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = parse_input(&input);
    let mut stdin = std::io::BufWriter::new(p.stdin.take().unwrap());
    let mut stdout = std::io::BufReader::new(p.stdout.take().unwrap());

    _ = writeln!(stdin, "{} {} {}", input.n, input.m, input.t);

    for i in 0..input.seed_count() {
        let s = input.x[i].iter().map(|x| x.to_string()).join(" ");
        _ = writeln!(stdin, "{}", s);
    }

    _ = stdin.flush();
    let mut sim = Sim::new(&input);

    for _ in 0..input.t {
        let mut a = vec![];
        let mut set = HashSet::new();

        for _ in 0..input.n {
            let line = read_line(&mut stdout, local)?;
            let mut s = line.split_whitespace();
            let mut aa = vec![];

            for _ in 0..input.n {
                let Some(v) = s.next() else {
                    return Err(format!("Invalid query format: {}", line));
                };

                let v = read(Some(v), 0, input.seed_count() - 1)?;

                if set.insert(v) {
                    aa.push(v);
                } else {
                    return Err(format!("Seed {} is used multiple times", v));
                }
            }

            a.push(aa);

            if s.next().is_some() {
                return Err(format!("Invalid query format: {}", line));
            }
        }

        sim.query(&input, a);

        for i in 0..input.seed_count() {
            let s = sim.x.last().unwrap()[i]
                .iter()
                .map(|x| x.to_string())
                .join(" ");
            _ = writeln!(stdin, "{}", s);
        }

        _ = stdin.flush();
    }

    let out = Output::new(sim, vec![]);
    compute_score(&input, &out, out.sim.turn)
}
