use std::env;
use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;
use std::time::Instant;

fn main() -> io::Result<()> {
   
    let args: Vec<String> = env::args().collect();
  
    let nome_arquivo_entrada = &args[1];

    let file = File::open(nome_arquivo_entrada)?;
    let reader = BufReader::new(file);

    let mut dados: Vec<i32> = Vec::new();
    for line in reader.lines() {
        let num_str = line?;
        match num_str.trim().parse::<i32>() {
            Ok(num) => dados.push(num),
            Err(e) => {
                eprintln!("Erro ao converter número: {}", e);
                std::process::exit(1);
            }
        }
    }

    
    let inicio = Instant::now(); //inicio
    dados.sort();                   //ordena
    let duracao = inicio.elapsed().as_secs_f64();   //fim e duracao

    //diretorio atual
    let current_dir = env::current_dir()?;
    let pasta = current_dir.file_name().unwrap().to_string_lossy();

    //CSV se nao existe new file
    let csv_path = "tempos_ordenacao_rust_timed.csv";
    let new_file = !Path::new(csv_path).exists();

    let mut csv_file = OpenOptions::new()
        .create(true)
        .append(true)
        .open(csv_path)?;

    if new_file {
        writeln!(csv_file, "Pasta;Arquivo;Tempo_Segundos")?;
    }

    writeln!(
        csv_file,
        "{};{};{:.6}",
        pasta, nome_arquivo_entrada, duracao
    )?;

    Ok(())
}

