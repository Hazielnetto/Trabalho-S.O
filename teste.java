import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;
import java.io.File;
import java.io.FileInputStream;

public class teste {

    public static void main(String[] args) throws IOException {

    Scanner sc = new Scanner(System.in);
    
    InputStream inputStream = null;
    OutputStream outputStream = null;

    System.out.print("Arquivo de entrada: ");
    String inputFileName = sc.next();
    
    File inputFile = new File(inputFileName);
    String dir = inputFile.getAbsolutePath();
    //File file = dir.listFiles((dir1, name) -> name.equals(inputFileName))[0]; 
    System.out.println(inputFile);

    // if (!inputf.contains(".zip")){
    //     inputf = (inputf+".zip");
    // }    
    
    System.out.print("Arquivo de saída (txt): ");
    File outputFile = new File(sc.next());

    // if (!outputf.contains(".txt")){
    //     outputf = (outputf+".txt");
    // }    

    sc.close();

        int TAMANHO_BUFFER = 8192;        
        byte[] buffer = new byte[TAMANHO_BUFFER];        

        long fs = inputFile.length();

        long startTime = System.currentTimeMillis();
        System.out.println(startTime);

        try {
            inputStream = new FileInputStream(inputFile);
            outputStream = new FileOutputStream(outputFile);

            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            long elapsedTime = System.currentTimeMillis() - startTime;
            System.out.println(
                "\nTamanho do arquivo: " + fs + " Bytes" + '(' + ')' +
                "\nTempo de execução: " + elapsedTime / 1000 + " segundos" +
                "\nTamanho do buffer: " + TAMANHO_BUFFER + " Bytes" + '(' + ')'
            );
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (inputStream != null) {
                    inputStream.close();
                }
                if (outputStream != null) {
                    outputStream.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
