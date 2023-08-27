use std::io::prelude::*;
use tools::*;

fn main() {
    if std::env::args().len() != 2 {
        eprintln!("Usage: {} seeds.txt", std::env::args().nth(0).unwrap());
        return;
    }
    if !std::path::Path::new("in").exists() {
        std::fs::create_dir("in").unwrap();
    }
    let f = std::env::args().nth(1).unwrap();
    let f = std::fs::File::open(&f).unwrap_or_else(|_| {
        eprintln!("no such file: {}", f);
        std::process::exit(1);
    });

    let f = std::io::BufReader::new(f);
    let mut id = 0;
    for line in f.lines() {
        let line = line.unwrap();
        let line = line.trim();
        let tokens = line.split_whitespace().collect::<Vec<&str>>();
        let parse_failed_msg = format!("{}: parse failed: {}", id, line);
        let (seed, l, n, s) = if tokens.len() == 1 {
            (
                tokens[0].parse::<u64>().expect(&parse_failed_msg),
                None,
                None,
                None,
            )
        } else {
            (
                tokens[0].parse::<u64>().expect(&parse_failed_msg),
                Some(tokens[1].parse::<usize>().expect(&parse_failed_msg)),
                Some(tokens[2].parse::<usize>().expect(&parse_failed_msg)),
                Some(tokens[3].parse::<usize>().expect(&parse_failed_msg)),
            )
        };
        let input = gen(
            seed,
            l.filter(|&l| l > 0),
            n.filter(|&n| n > 0),
            s.filter(|&s| s > 0),
        )
        .map_err(|e| format!("{}: {}", id, e))
        .unwrap();
        let mut w =
            std::io::BufWriter::new(std::fs::File::create(format!("in/{:04}.txt", id)).unwrap());
        write!(w, "{}", input).unwrap();
        id += 1;
    }
}
