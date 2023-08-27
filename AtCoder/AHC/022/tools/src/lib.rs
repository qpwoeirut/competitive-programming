use rand::prelude::*;
use rand::seq::SliceRandom;
use rand::{Rng, SeedableRng};
use rand_distr::Normal;
use std::str::Lines;
use svg::node::{
    element::{Circle, Line, Rectangle, Text as TextElement, Title},
    Text, Value,
};

#[cfg(target_arch = "wasm32")]
use wasm_bindgen::prelude::*;

const MIN_L: usize = 10;
const MAX_L: usize = 50;
const MIN_N: usize = 60;
const MAX_N: usize = 100;
const MIN_S_SQRT: usize = 1;
const MAX_S_SQRT: usize = 30;
const MAX_MEASURE_CNT: usize = 10000;
const MIN_S: usize = MIN_S_SQRT * MIN_S_SQRT;
const MAX_S: usize = MAX_S_SQRT * MAX_S_SQRT;
pub const MIN_P: usize = 0;
pub const MAX_P: usize = 1000;

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
        Err(format!("Unexpected end of line"))
    }
}

pub struct TesterInput {
    pub l: usize,
    pub n: usize,
    pub s: usize,
    pub out_coordinate: Vec<(usize, usize)>,
    pub out_idx: Vec<usize>,
    pub noises: Vec<i64>,
}

impl std::fmt::Display for TesterInput {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {}", self.l, self.n, self.s)?;

        for (r, c) in self.out_coordinate.iter() {
            writeln!(f, "{} {}", r, c)?;
        }

        for idx in self.out_idx.iter() {
            writeln!(f, "{}", idx)?;
        }

        for noise in self.noises.iter() {
            writeln!(f, "{}", noise)?;
        }

        Ok(())
    }
}

impl std::str::FromStr for TesterInput {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut tokens = s.split_whitespace();
        let l = read(tokens.next(), MIN_L, MAX_L)?;
        let n = read(tokens.next(), MIN_N, MAX_N)?;
        let s = read(tokens.next(), MIN_S, MAX_S)?;

        let mut out_coordinate = Vec::new();
        for _ in 0..n {
            out_coordinate.push((
                read(tokens.next(), 0, l - 1)?,
                read(tokens.next(), 0, l - 1)?,
            ));
        }

        let mut out_idx = Vec::new();
        for _ in 0..n {
            out_idx.push(read(tokens.next(), 0, n - 1)?);
        }

        let mut noises = Vec::new();
        for _ in 0..MAX_MEASURE_CNT {
            noises.push(read(tokens.next(), i64::MIN, i64::MAX)?);
        }

        Ok(TesterInput {
            l,
            n,
            s,
            out_coordinate,
            out_idx,
            noises,
        })
    }
}

pub fn validate_measure(line: &str, l: usize, n: usize) -> Result<MeasureOp, String> {
    let mut tokens = line.split_whitespace();
    let i = read(tokens.next(), -1, n as i32 - 1);
    let i = i.map_err(|err| format!("i: {}", err))?;
    let y = read(tokens.next(), -(l as i32 - 1), l as i32 - 1);
    let y = y.map_err(|err| format!("y: {}", err))?;
    let x = read(tokens.next(), -(l as i32 - 1), l as i32 - 1);
    let x = x.map_err(|err| format!("x: {}", err))?;
    if i == -1 && y == -1 && x == -1 {
        Ok(MeasureOp {
            i: 0,
            y: 0,
            x: 0,
            end: true,
        })
    } else if i < 0 {
        Err(format!("Unexpected measure operation: {} {} {}", i, y, x))
    } else {
        let i = i as usize;
        Ok(MeasureOp {
            i,
            y,
            x,
            end: false,
        })
    }
}

// ----- gen -----

pub fn gen(
    seed: u64,
    l: Option<usize>,
    n: Option<usize>,
    s: Option<usize>,
) -> Result<TesterInput, String> {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);

    // Generate l, n, and s
    let l: usize = l.unwrap_or(rng.gen_range(MIN_L as u64..=MAX_L as u64) as usize);
    let n: usize = n.unwrap_or(rng.gen_range(MIN_N as u64..=MAX_N as u64) as usize);
    let s = match s {
        Some(s) => s,
        None => {
            let s = rng.gen_range(MIN_S_SQRT as u64..=MAX_S_SQRT as u64) as usize;
            s * s
        }
    };

    if !(MIN_L..=MAX_L).contains(&l) {
        return Err(format!("l must be in range[{MIN_L}, {MAX_L}]"));
    }
    if !(MIN_N..=MAX_N).contains(&n) {
        return Err(format!("n must be in range[{MIN_N}, {MAX_N}]"));
    }
    if !(MIN_S..=MAX_S).contains(&s) {
        return Err(format!("s must be in range[{MIN_S}, {MAX_S}]"));
    }

    // Generate out_coordinate
    // shuffle [0, 1, ... L*L-1] and select first n elements.
    let mut v_cor = vec![0; l * l];
    for i in 0..l * l {
        v_cor[i] = i;
    }
    v_cor.shuffle(&mut rng);
    let mut out_coordinate = Vec::new();
    for i in 0..n {
        out_coordinate.push((v_cor[i] / l, v_cor[i] % l));
    }
    out_coordinate.sort();

    // Generate out_idx
    // shuffle [0, ... , n-1]
    let mut v_idx = vec![0; n];
    for i in 0..n {
        v_idx[i] = i;
    }
    v_idx.shuffle(&mut rng);
    let mut out_idx = Vec::new();
    for i in 0..n {
        out_idx.push(v_idx[i]);
    }

    // Generate noises from normal distribution
    let mut noises = Vec::new();
    let dist = Normal::<f64>::new(0f64, s as f64).map_err(|e| e.to_string())?;
    for _ in 0..MAX_MEASURE_CNT {
        let noise = dist.sample(&mut rng);
        let noise = noise.round() as i64;
        noises.push(noise);
    }

    Ok(TesterInput {
        l,
        n,
        s,
        out_coordinate,
        out_idx,
        noises,
    })
}

#[cfg(target_arch = "wasm32")]
#[wasm_bindgen]
pub fn generate(
    seed: u64,
    l: Option<usize>,
    n: Option<usize>,
    s: Option<usize>,
) -> Result<String, JsError> {
    let l = l.filter(|&l| l != 0);
    let s = s.filter(|&s| s != 0);
    let n = n.filter(|&n| n != 0);
    gen(seed, l, n, s)
        .map(|t| t.to_string())
        .map_err(|e| JsError::new(&e))
}

// ----- tester -----
pub struct ArrangeOp {
    pub p: Vec<Vec<usize>>,
}

pub struct MeasureOp {
    pub i: usize,
    pub y: i32,
    pub x: i32,
    pub end: bool,
}

pub struct AnswerOp {
    pub estimate: Vec<usize>,
}

pub struct Outcome {
    pub score: u64,
    pub wrong_answer: usize,
    pub arrange_cost: u64,
    pub measure_cost: u64,
    pub measure_cnt: usize,
}

pub struct Sim {
    pub l: usize,
    pub n: usize,
    pub s: usize,
    pub out_coordinate: Vec<(usize, usize)>,
    pub out_idx: Vec<usize>,
    pub p: Vec<Vec<usize>>,
    pub noises: Vec<i64>,
    pub w: usize,
    pub arrange_cost: u64,
    pub measure_cnt: usize,
    pub measure_cost: u64,
    pub score: u64,
}

impl Sim {
    pub fn new(input: &TesterInput) -> Self {
        Sim {
            l: input.l,
            n: input.n,
            s: input.s,
            out_coordinate: input.out_coordinate.clone(),
            out_idx: input.out_idx.clone(),
            p: vec![vec![0; input.l]; input.l],
            noises: input.noises.clone(),
            w: 0,
            arrange_cost: 0,
            measure_cnt: 0,
            measure_cost: 0,
            score: 0,
        }
    }

    fn calc_arrange_cost(&self, p: &Vec<Vec<usize>>) -> u64 {
        let mut res = 0;
        for i in 0..self.l {
            for j in 0..self.l {
                res += (p[i][j] - p[(i + 1) % self.l][j]).pow(2) as u64
                    + (p[i][j] - p[i][(j + 1) % self.l]).pow(2) as u64;
            }
        }
        res
    }

    pub fn arrange(&mut self, op: &ArrangeOp) -> () {
        self.p = op.p.clone();

        // コスト計算
        let cost = self.calc_arrange_cost(&self.p);
        self.arrange_cost = cost;
    }

    pub fn measure(&mut self, op: &MeasureOp) -> Result<(usize, usize), String> {
        assert!(!op.end, "This statement must not be reached");

        self.measure_cnt += 1;
        if self.measure_cnt > MAX_MEASURE_CNT {
            return Err(format!("Too many measure"));
        }
        self.measure_cost += 100 * (10 + op.y.abs() as u64 + op.x.abs() as u64);

        let y = if op.y >= 0 {
            op.y as usize
        } else {
            self.l - op.y.abs() as usize
        };

        let x = if op.x >= 0 {
            op.x as usize
        } else {
            self.l - op.x.abs() as usize
        };

        let idx = self.out_idx[op.i];
        let (out_r, out_c) = self.out_coordinate[idx];
        let r = (out_r + y) % self.l;
        let c = (out_c + x) % self.l;

        let sample = (self.p[r][c] as i64)
            .checked_add(self.noises[self.measure_cnt - 1])
            .ok_or_else(|| {
                format!(
                    "noise {} is too big. The value is {}",
                    self.measure_cnt - 1,
                    self.noises[self.measure_cnt - 1]
                )
            })?;
        let res = sample.max(MIN_P as i64).min(MAX_P as i64) as usize;

        Ok((self.p[r][c], res))
    }

    pub fn answer(&mut self, op: &AnswerOp) {
        for i in 0..self.n {
            if op.estimate[i] != self.out_idx[i] {
                self.w += 1;
            }
        }
    }

    pub fn compute_score(&mut self) -> u64 {
        let score = (1e14 * 0.8f64.powf(self.w as f64))
            / (self.arrange_cost + self.measure_cost + 100000) as f64;
        self.score = score.ceil() as u64;
        self.score
    }
}

// ----- vis -----
pub struct MeasureOpWithComment {
    comments: Vec<String>,
    op: MeasureOp,
}

pub struct ContestantOutput {
    arrange_op: ArrangeOp,
    measure_ops: Vec<MeasureOpWithComment>,
    answer_op: AnswerOp,
}

pub struct VisualizeData {
    pub input: TesterInput,
    pub output: ContestantOutput,
}

pub fn get_line(lines: &mut Lines) -> Result<String, String> {
    loop {
        let line = lines
            .next()
            .ok_or_else(|| format!("Output has ended unexpectedly"))?;
        if line.trim().len() == 0 || line.starts_with("#") {
            continue;
        }
        return Ok(format!("{}", line));
    }
}

pub fn get_line_with_comment(lines: &mut Lines) -> Result<(String, Vec<String>), String> {
    let mut comments = Vec::new();
    loop {
        let line = lines
            .next()
            .ok_or_else(|| format!("Output has ended unexpectedly"))?;
        if line.trim().len() == 0 {
            continue;
        }
        if let Some(comment) = line.strip_prefix("#") {
            comments.push(comment.trim().to_owned());
        } else {
            return Ok((line.to_owned(), comments));
        }
    }
}

pub fn parse_row(out: &str, l: usize) -> Result<Vec<usize>, String> {
    let row = out
        .split_whitespace()
        .map(|e| e.parse::<usize>().map_err(|e| e.to_string()))
        .collect::<Vec<_>>();

    if row.len() != l {
        return Err(format!(
            "A single row must contain exactly L (= {}) elements but actually has {} elements.",
            l,
            row.len()
        ));
    }
    let mut res = Vec::new();
    for (j, elm) in row.iter().enumerate() {
        match elm {
            Ok(val) => {
                if !(MIN_P <= *val && *val <= MAX_P) {
                    return Err(format!(
                        "{}-th element: Values of P must be between {} and {}.",
                        j, MIN_P, MAX_P
                    ));
                }
                res.push(*val);
            }
            Err(err) => {
                return Err(format!("{}-th element: {}", j, err));
            }
        }
    }
    Ok(res)
}

pub fn parse_arrange(lines: &mut Lines, l: usize) -> Result<ArrangeOp, String> {
    let mut p = Vec::new();
    for i in 0..l {
        let line = get_line(lines);
        let row = line.and_then(|line| parse_row(&line, l));
        let row = row.map_err(|err| format!("{}-th row: {}", i, err))?;
        p.push(row);
    }
    Ok(ArrangeOp { p })
}

pub fn parse_measure(
    lines: &mut Lines,
    n: usize,
    l: usize,
) -> Result<MeasureOpWithComment, String> {
    let (line, comments) = get_line_with_comment(lines)?;
    let op = validate_measure(&line, l, n)?;
    Ok(MeasureOpWithComment { comments, op })
}

pub fn parse_answer(lines: &mut Lines, n: usize) -> Result<AnswerOp, String> {
    let mut estimate = Vec::new();
    for i in 0..n {
        let line = get_line(lines);
        let e = line.and_then(|line| read(Some(line.trim()), 0, n - 1));
        let e = e.map_err(|err| format!("{}-th answer: {}", i, err))?;
        estimate.push(e);
    }
    Ok(AnswerOp { estimate })
}

pub fn parse_visualize_data(input: &str, output: &str) -> Result<VisualizeData, String> {
    let input = input.parse::<TesterInput>()?;
    let mut lines = output.trim().lines();
    // parse arrange
    let arrange_op = parse_arrange(&mut lines, input.l);
    let arrange_op = arrange_op.map_err(|err| format!("Placement: {}", err))?;
    // parse measure
    let mut measure_ops = Vec::new();
    loop {
        let measure_op = parse_measure(&mut lines, input.n, input.l);
        let measure_op = measure_op
            .map_err(|err| format!("Measurement: {}-th measure: {}", measure_ops.len(), err))?;

        if measure_op.op.end {
            break;
        }
        measure_ops.push(measure_op);

        if measure_ops.len() > MAX_MEASURE_CNT {
            return Err(format!("Measurement: Too many measure"));
        }
    }
    // parse answer
    let answer_op = parse_answer(&mut lines, input.n);
    let answer_op = answer_op.map_err(|err| format!("Answer: {}", err))?;
    let output = ContestantOutput {
        arrange_op,
        measure_ops,
        answer_op,
    };
    Ok(VisualizeData { input, output })
}

#[cfg_attr(target_arch = "wasm32", wasm_bindgen(getter_with_clone))]
pub struct SolInfo {
    pub error: Option<String>,
    pub arrange_cost: u64,
    pub measure_cost: u64,
    pub score: u64,
    pub max_turn: usize,
    pub min_p: usize,
    pub max_p: usize,
    pub is_correct_answer: Vec<usize>,
}

#[cfg(target_arch = "wasm32")]
#[wasm_bindgen]
pub fn get_sol_info(input: &str, output: &str) -> Result<SolInfo, JsError> {
    let data = parse_visualize_data(input, output).map_err(|e| JsError::new(&e))?;
    Ok(validate_sol(&data))
}

pub fn validate_sol(data: &VisualizeData) -> SolInfo {
    let mut sim = Sim::new(&data.input);
    let mut invalid_op = None;
    sim.arrange(&data.output.arrange_op);
    let mut min_p = MAX_P;
    let mut max_p = MIN_P;
    for i in 0..sim.l {
        for j in 0..sim.l {
            max_p = max_p.max(data.output.arrange_op.p[i][j]);
            min_p = min_p.min(data.output.arrange_op.p[i][j]);
        }
    }
    let measures = &data.output.measure_ops;
    for t in 0..measures.len() {
        let op = &measures[t].op;
        match sim.measure(op) {
            Ok(_) => {}
            Err(err) => {
                invalid_op = Some((t, err));
                break;
            }
        }
    }

    if let Some((first_fail_turn, err)) = invalid_op {
        return SolInfo {
            error: Some(err),
            arrange_cost: sim.arrange_cost,
            measure_cost: sim.measure_cost,
            score: 0,
            max_turn: first_fail_turn,
            min_p,
            max_p,
            is_correct_answer: vec![0; sim.n],
        };
    }

    sim.answer(&data.output.answer_op);

    let mut is_correct_answer = vec![0; sim.n];
    for i in 0..sim.n {
        let same = data.output.answer_op.estimate[i] == sim.out_idx[i];
        is_correct_answer[i] = same as usize;
    }

    sim.compute_score();
    SolInfo {
        error: None,
        arrange_cost: sim.arrange_cost,
        measure_cost: sim.measure_cost,
        score: sim.score,
        max_turn: data.output.measure_ops.len(),
        min_p,
        max_p,
        is_correct_answer,
    }
}

fn rect<V: Into<Value>>(
    x: V,
    y: V,
    w: V,
    h: V,
    fill: &str,
    opacity: f64,
    stroke: Option<&str>,
    stroke_width: Option<usize>,
    title: Option<&str>,
) -> Rectangle {
    let mut rect = Rectangle::new()
        .set("x", x)
        .set("y", y)
        .set("width", w)
        .set("height", h)
        .set("fill", fill)
        .set("fill-opacity", opacity);

    rect = match stroke {
        Some(stroke) => rect.set("stroke", stroke),
        None => rect,
    };
    rect = match stroke_width {
        Some(stroke_width) => rect.set("stroke-width", stroke_width),
        None => rect,
    };
    if let Some(tooltip) = title {
        rect.add(Title::new().add(Text::new(tooltip)))
    } else {
        rect
    }
}

fn line<V: Into<Value>>(x1: V, y1: V, x2: V, y2: V, stroke: &str, stroke_width: usize) -> Line {
    Line::new()
        .set("x1", x1)
        .set("y1", y1)
        .set("x2", x2)
        .set("y2", y2)
        .set("stroke", stroke)
        .set("stroke-width", stroke_width)
}

fn circle<V: Into<Value>>(
    cx: V,
    cy: V,
    r: V,
    fill: &str,
    stroke: &str,
    stroke_width: usize,
) -> Circle {
    Circle::new()
        .set("cx", cx)
        .set("cy", cy)
        .set("r", r)
        .set("fill", fill)
        .set("stroke", stroke)
        .set("stroke-width", stroke_width)
}

// get color from heatmap
fn get_color(val: usize, lb: usize, ub: usize) -> String {
    // white: #FFFFFF
    const START_RED: u8 = 0xFF;
    const START_GREEN: u8 = 0xFF;
    const START_BLUE: u8 = 0xFF;
    // orangered: #FF4500
    const END_RED: u8 = 0xFF;
    const END_GREEN: u8 = 0x45;
    const END_BLUE: u8 = 0x00;

    let rate = if lb == ub || val < lb {
        0.0
    } else if val > ub {
        1.0
    } else {
        (val - lb) as f64 / (ub - lb) as f64
    };
    let r = (START_RED as f64 - (START_RED - END_RED) as f64 * rate).round() as u8;
    let g = (START_GREEN as f64 - (START_GREEN - END_GREEN) as f64 * rate).round() as u8;
    let b = (START_BLUE as f64 - (START_BLUE - END_BLUE) as f64 * rate).round() as u8;

    let buf = [r, g, b];
    let str = buf.iter().map(|x| format!("{:02X}", x)).collect::<String>();
    "#".to_string() + &str
}

pub struct MeasureInfo {
    pub i: usize,
    pub y: i32,
    pub x: i32,
    pub p: usize,
    pub m: usize,
    pub comment: Option<String>,
}

#[derive(Clone)]
pub struct Tooltip {
    pub p: String,
    pub out: Option<String>,
    pub measure_val: Option<String>,
}

impl Tooltip {
    fn new() -> Self {
        Tooltip {
            p: format!(""),
            out: None,
            measure_val: None,
        }
    }
}

pub fn vis(
    data: &VisualizeData,
    turn: usize,
    col_lb: usize,
    col_ub: usize,
) -> Result<VisResult, String> {
    const W: usize = 18;
    let input = &data.input;
    let output = &data.output;

    let mut tooltips = vec![vec![Tooltip::new(); input.l]; input.l];

    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (-5, -5, W * input.l + 10, W * input.l + 10))
        .set("width", W * input.l + 10)
        .set("height", W * input.l + 10);

    // Draw outer frame
    doc = doc.add(rect(
        -5,
        -5,
        (W * input.l + 10) as i32,
        (W * input.l + 10) as i32,
        "white",
        1.0,
        Some("none"),
        Some(0),
        None,
    ));

    // Draw grid
    for i in 0..=input.l {
        doc = doc.add(line(0, i * W, W * input.l, i * W, "lightgray", 1));
        doc = doc.add(line(i * W, 0, i * W, W * input.l, "lightgray", 1));
    }

    let mut sim = Sim::new(input);
    sim.arrange(&output.arrange_op);

    // heatmap of P[i][j]
    for i in 0..input.l {
        for j in 0..input.l {
            // colorize P[i][j]
            let color = get_color(sim.p[i][j], col_lb, col_ub);
            doc = doc.add(rect(j * W, i * W, W, W, &color, 1.0, None, None, None));
            // Add tooltip
            tooltips[i][j].p = format!("P[{}][{}]={}", i, j, sim.p[i][j]);
            doc = doc.add(rect(j * W, i * W, W, W, "white", 0.0, None, None, None));
        }
    }

    let mut last_measure = None;
    for (i, measure_op) in output.measure_ops.iter().enumerate() {
        let (p, m) = sim.measure(&measure_op.op)?;
        if i == turn - 1 {
            let comment = if measure_op.comments.is_empty() {
                None
            } else {
                Some(measure_op.comments.join("\n"))
            };
            last_measure = Some(MeasureInfo {
                i: measure_op.op.i,
                y: measure_op.op.y,
                x: measure_op.op.x,
                p,
                m,
                comment,
            });
        }
    }

    // hilight last_measure
    if let Some(last_measure) = &last_measure {
        let i = last_measure.i;
        let y = last_measure.y;
        let x = last_measure.x;

        let y = if y >= 0 {
            y as usize
        } else {
            sim.l - y.abs() as usize
        };
        let x = if x >= 0 {
            x as usize
        } else {
            sim.l - x.abs() as usize
        };

        let (r, c) = sim.out_coordinate[sim.out_idx[i]];

        // movement line
        let sr = r as i32;
        let sc = c as i32;
        let tr = sr + last_measure.y;
        let tc = sc + last_measure.x;
        let w = W as i32;
        for i in -1..=1 {
            for j in -1..=1 {
                doc = doc.add(line(
                    (sc + j * sim.l as i32) * w + w / 2,
                    (sr + i * sim.l as i32) * w + w / 2,
                    (tc + j * sim.l as i32) * w + w / 2,
                    (tr + i * sim.l as i32) * w + w / 2,
                    "gray",
                    1,
                ));
            }
        }

        // start cell
        doc = doc.add(rect(
            c as i32 * w - 1,
            r as i32 * w - 1,
            w + 2,
            w + 2,
            "none",
            1.0,
            Some("purple"),
            Some(1),
            None,
        ));

        // target cell
        let r = (r + y) % sim.l;
        let c = (c + x) % sim.l;
        doc = doc.add(rect(
            c * W,
            r * W,
            W,
            W,
            "none",
            1.0,
            Some("lime"),
            Some(2),
            None,
        ));

        // save tooltip info
        tooltips[r][c].measure_val = Some(format!("Measured value is {}", last_measure.m));
    };

    let mut out_idx_rev = vec![0; sim.n];
    for i in 0..sim.out_idx.len() {
        out_idx_rev[sim.out_idx[i]] = i;
    }

    // draw out cell
    for (i, (r, c)) in sim.out_coordinate.iter().enumerate() {
        // draw circle
        doc = doc.add(circle(
            *c * W + W / 2,
            *r * W + W / 2,
            W / 2 * 4 / 5,
            "royalblue",
            "none",
            1,
        ));

        // draw number
        doc = doc.add(
            TextElement::new()
                .add(Text::new(format!("{}", out_idx_rev[i])))
                .set("x", c * W + W / 2)
                .set("y", r * W + W / 2 + 1)
                .set("font-size", W - 9)
                .set("font-family", "sans-serif")
                .set("fill", "whitesmoke")
                .set("text-anchor", "middle")
                .set("dominant-baseline", "middle")
                .set(
                    "style",
                    "stroke-width: 0.5; stroke: whitesmoke; paint-order: stroke;",
                ),
        );

        // save tooltip info
        tooltips[*r][*c].out = Some(format!(
            "Exit cell {} corresponds to wormhole {}",
            i, out_idx_rev[i]
        ));
    }

    // Draw tooltips
    for i in 0..input.l {
        for j in 0..input.l {
            let mut tooltip = format!("{}", tooltips[i][j].p);
            if let Some(measure_val) = &tooltips[i][j].measure_val {
                tooltip = tooltip + "\n" + measure_val;
            }
            if let Some(out) = &tooltips[i][j].out {
                tooltip = tooltip + "\n" + out;
            }
            doc = doc.add(rect(
                j * W,
                i * W,
                W,
                W,
                "black",
                0.0,
                None,
                None,
                Some(&tooltip),
            ));
        }
    }

    let comment = if let Some(measure_info) = &last_measure {
        measure_info.comment.clone().unwrap_or_else(|| format!(""))
    } else {
        format!("")
    };
    Ok(VisResult {
        error: format!(""),
        svg: doc.to_string(),
        comment,
        measure: last_measure.map(
            |MeasureInfo {
                 i,
                 y,
                 x,
                 p,
                 m,
                 comment: _comment,
             }| MeasureResult { i, y, x, p, m },
        ),
    })
}

#[cfg_attr(target_arch = "wasm32", wasm_bindgen(getter_with_clone))]
#[derive(Clone)]
pub struct MeasureResult {
    pub i: usize,
    pub y: i32,
    pub x: i32,
    pub p: usize, // true value
    pub m: usize, // measured value
}

#[cfg_attr(target_arch = "wasm32", wasm_bindgen(getter_with_clone))]
pub struct VisResult {
    pub error: String,
    pub svg: String,
    pub comment: String,
    pub measure: Option<MeasureResult>,
}

#[cfg(target_arch = "wasm32")]
#[wasm_bindgen]
pub fn visualize(
    input: &str,
    output: &str,
    t: usize,
    col_lb: usize,
    col_ub: usize,
) -> Result<VisResult, JsError> {
    let data = parse_visualize_data(input, output).map_err(|e| JsError::new(&e))?;

    let sol_info = validate_sol(&data);
    if let Some(err) = sol_info.error {
        return Err(JsError::new(&err));
    }

    if t <= sol_info.max_turn {
        vis(&data, t, col_lb, col_ub).map_err(|e| JsError::new(&e))
    } else {
        Err(JsError::new("index out of bounds"))
    }
}
