use tools::*;

fn main() {
    if std::env::args().len() != 3 {
        eprintln!(
            "Usage: {} <tester input> <tester output>",
            std::env::args().nth(0).unwrap()
        );
        return;
    }
    let in_file = std::env::args().nth(1).unwrap();
    let in_data = std::fs::read_to_string(&in_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", in_file);
        std::process::exit(1);
    });
    let out_file = std::env::args().nth(2).unwrap();
    let out_data = std::fs::read_to_string(&out_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", out_file);
        std::process::exit(1);
    });
    let vis_data = parse_visualize_data(&in_data, &out_data).unwrap();
    let sol_info = validate_sol(&vis_data);
    if let Some(err) = sol_info.error {
        eprintln!("{}", err);
    }
    eprintln!("Score = {}", sol_info.score);

    let vis_result = vis(&vis_data, sol_info.max_turn, sol_info.min_p, sol_info.max_p);
    match vis_result {
        Ok(vis_result) => {
            if vis_result.error.len() > 0 {
                println!("{}", vis_result.error);
            }
            let svg_str = format!("<html><body>{}</body></html>", vis_result.svg);
            std::fs::write("vis.html", svg_str).unwrap();
        },
        Err(err) => {
            println!("{}", err);
        }
    }
}
