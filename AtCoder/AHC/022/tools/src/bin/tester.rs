use std::io::{prelude::*, BufReader, BufWriter};
use std::process::{ChildStdout, Stdio};
use tools::*;

fn read_line(stdout: &mut BufReader<ChildStdout>) -> Result<String, String> {
    loop {
        let mut out = String::new();
        match stdout.read_line(&mut out) {
            Ok(0) | Err(_) => {
                return Err(format!("Your program has terminated unexpectedly"));
            }
            _ => (),
        }
        if out.trim().len() == 0 {
            return Err(format!("Enexpected empty line"));
        }
        print!("{}", out);
        if out.starts_with("#") {
            continue;
        }
        return Ok(out);
    }
}

fn read_arrange(stdout: &mut BufReader<ChildStdout>, l: usize) -> Result<ArrangeOp, String> {
    let mut p = Vec::new();
    let mut res_err = None;
    for _ in 0..l {
        let out = read_line(stdout)?;
        let row = parse_row(&out, l);
        match row {
            Ok(row) => {
                p.push(row);
            }
            Err(err) => {
                res_err.get_or_insert(err);
            }
        }
    }
    match res_err {
        Some(err) => Err(err),
        None => Ok(ArrangeOp { p }),
    }
}

fn read_measure(
    stdout: &mut BufReader<ChildStdout>,
    l: usize,
    n: usize,
) -> Result<MeasureOp, String> {
    let out = read_line(stdout)?;
    validate_measure(&out, l, n)
}

fn read_answer(stdout: &mut BufReader<ChildStdout>, n: usize) -> Result<AnswerOp, String> {
    let mut estimate = Vec::new();
    for _ in 0..n {
        let out = read_line(stdout)?;
        let i = read(Some(out.trim()), 0, n - 1)?;
        estimate.push(i);
    }
    Ok(AnswerOp { estimate })
}

fn exec(p: &mut std::process::Child) -> Result<Outcome, String> {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = input.parse::<TesterInput>()?;
    let mut stdin = BufWriter::new(p.stdin.take().unwrap());
    let mut stdout = BufReader::new(p.stdout.take().unwrap());

    let l = input.l;
    let n = input.n;
    let s = input.s;
    writeln!(stdin, "{} {} {}", l, n, s).map_err(|e| e.to_string())?;
    for (r, c) in input.out_coordinate.iter() {
        writeln!(stdin, "{} {}", r, c).map_err(|e| e.to_string())?;
    }
    stdin.flush().map_err(|e| e.to_string())?;

    let mut sim = Sim::new(&input);
    // arrange
    let arrange_res = read_arrange(&mut stdout, l);

    if let Ok(op) = &arrange_res {
        sim.arrange(op);
    }

    // measure
    loop {
        let measure_res = read_measure(&mut stdout, l, n);

        let op = match measure_res {
            Ok(op) => op,
            Err(err) => {
                writeln!(stdin, "-1").map_err(|e| e.to_string())?;
                return Err(err);
            }
        };

        if op.end {
            break;
        }

        // return -1 here if arrange is fail.
        if sim.measure_cnt == 0 {
            if let Err(err) = &arrange_res {
                writeln!(stdin, "-1").map_err(|e| e.to_string())?;
                return Err(err.clone());
            }
        }

        let measure_res = sim.measure(&op);
        match measure_res {
            Ok((_, m)) => writeln!(stdin, "{}", m).map_err(|e| e.to_string())?,
            Err(err) => {
                writeln!(stdin, "-1").map_err(|e| e.to_string())?;
                return Err(err);
            }
        }
        stdin.flush().unwrap();
    }

    if let Err(err) = &arrange_res {
        return Err(err.clone());
    }

    // answer
    let op = read_answer(&mut stdout, input.n)?;
    sim.answer(&op);
    sim.compute_score();

    Ok(Outcome {
        score: sim.score,
        wrong_answer: sim.w,
        arrange_cost: sim.arrange_cost,
        measure_cost: sim.measure_cost,
        measure_cnt: sim.measure_cnt,
    })
}

fn main() {
    if std::env::args().len() < 2 {
        eprintln!(
            "Usage: {} <command> [<args>...]",
            std::env::args().nth(0).unwrap()
        );
        return;
    }
    let (command, args) = (
        std::env::args().nth(1).unwrap(),
        std::env::args().skip(2).collect::<Vec<_>>(),
    );

    let mut p = std::process::Command::new(command)
        .args(args)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .unwrap_or_else(|e| {
            eprintln!("failed to execute the command");
            eprintln!("{}", e);
            std::process::exit(1)
        });

    match exec(&mut p) {
        Ok(outcome) => {
            eprintln!("Score = {}", outcome.score);
            eprintln!("Number of wrong answers = {}", outcome.wrong_answer);
            eprintln!("Placement cost   = {}", outcome.arrange_cost);
            eprintln!("Measurement cost = {}", outcome.measure_cost);
            eprintln!("Measurement count = {}", outcome.measure_cnt);
        }
        Err(err) => {
            eprintln!("{}", err);
            p.kill().unwrap();
        }
    }
}
