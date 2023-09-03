use std::io::{self};
use std::path::Path;

mod loader;

fn main() -> io::Result<()> {
    let filename = "../mazes/mazes.bin";

    if !Path::new(filename).exists() {
        return Err(io::Error::new(io::ErrorKind::NotFound, "File not found"));
    }

    println!("Reading mazes from {}", filename);
    let mazes = loader::read_mazes(filename, Some(vec![2, 5, 3, 2]))?;
    println!("Read {} mazes", mazes.len());

    // Print the mazes to check
    for (index, maze) in mazes.iter().enumerate() {
        println!("Maze #{}", index + 1);
        println!(
            "Length: {}, Size X: {}, Size Y: {}",
            maze.length, maze.size_x, maze.size_y
        );
        for row in &maze.tiles {
            for &tile in row {
                print!("{}", tile);
            }
            println!();
        }
        println!("------------------");
    }

    Ok(())
}
