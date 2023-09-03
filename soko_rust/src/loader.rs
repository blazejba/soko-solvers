use std::collections::HashSet;
use std::fs::File;
use std::io::{self, Read};
use std::path::Path;

#[derive(Debug)]
pub struct Maze {
    pub length: u8,
    pub size_x: u8,
    pub size_y: u8,
    pub tiles: Vec<Vec<u8>>,
}

pub fn read_mazes(filename: &str, indices: Option<Vec<usize>>) -> io::Result<Vec<Maze>> {
    let mut mazes = Vec::new();
    let mut file = File::open(Path::new(filename))?;

    let indices_set: HashSet<usize> = indices.unwrap_or_default().into_iter().collect();
    let mut file_bytes = file.bytes().peekable();

    let mut maze_index = 1;
    loop {
        if file_bytes.peek().is_none() {
            break;
        }

        let length: u8;
        let size_x: u8;
        let size_y: u8;

        println!("Reading maze #{}", maze_index);
        length = file_bytes.next().unwrap()?; // Reading a single byte
        size_x = file_bytes.next().unwrap()?;
        size_y = file_bytes.next().unwrap()?;

        let tiles_result: io::Result<Vec<Vec<u8>>> = (0..size_y)
            .map(|_| {
                let mut row = vec![0u8; size_x as usize];
                for i in 0..size_x {
                    row[i as usize] = file_bytes.next().ok_or(io::Error::new(
                        io::ErrorKind::UnexpectedEof,
                        "Failed to read byte",
                    ))??;                    
                }
                Ok(row)
            })
            .collect();

        let tiles = tiles_result?;

        let maze = Maze {
            length: length,
            size_x: size_x,
            size_y: size_y,
            tiles: tiles,
        };

        if indices_set.is_empty() || indices_set.contains(&maze_index) {
            mazes.push(maze);
        }

        maze_index += 1;
    }

    Ok(mazes)
}
