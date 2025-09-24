import java.io.*;
import java.nio.file.*;
import java.util.*;

public class sort_java_timed {

    public static void main(String[] args) throws Exception {
        String nomeArquivoEntrada = args[0];

        List<Integer> dados = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivoEntrada))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                dados.add(Integer.parseInt(linha.trim()));
            }
        }

        int[] array = dados.stream().mapToInt(i -> i).toArray();

        long inicio = System.nanoTime(); //inicio
        Arrays.sort(array);                //ordena
        long fim = System.nanoTime();       //fim

        double duracaoSegundos = (fim - inicio) / 1e9;

        Path pathAtual = Paths.get("").toAbsolutePath();
        String pasta = pathAtual.getFileName().toString();

        try (FileWriter fw = new FileWriter("tempos_ordenacao_java_timed.csv", true);
             BufferedWriter bw = new BufferedWriter(fw);
             PrintWriter out = new PrintWriter(bw)) {
            out.printf("%s;%s;%.6f%n", pasta, nomeArquivoEntrada, duracaoSegundos);
        }
    }
}

