import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

public class Trabalho_SO_Buffer {
  public static void main(String[] args)throws IOException {

    Scanner sc = new Scanner(System. in);
    InputStream inputStream = null;
    OutputStream outputStream = null;
    FileWriter writer = new FileWriter("log.txt", true);
    String inputFileName;

    if (args.length == 0) {
      System.out.print("Arquivo de entrada (0 para valor padrão): ");
      inputFileName = sc.nextLine();

      if (inputFileName.equals("0")) {
        inputFileName = "video";
      }
    } else {
      inputFileName = args[0];
    }

    File inputFile = new File(inputFileName);
    File dir = new File(inputFile.getAbsolutePath());

    String path = dir.toString();
    path = path.substring(0, path.lastIndexOf("\\") + 1);

    dir = new File(path);
    String fileExtension = "";

    for (File f : dir.listFiles()) {

      String fileName = f.getName();
      fileExtension = fileName.substring(fileName.lastIndexOf(".") + 1, f.getName().length());
      fileExtension = fileExtension.toLowerCase();

      if (fileName.equals(inputFile + "." + fileExtension)) {
        inputFile = new File(fileName);
      }
    }
    sc.close();
    String outputFile = ".\\outputs\\java\\" + inputFile.getName() + ".txt";

    int TAMANHO_BUFFER = 32768;
    byte[] buffer = new byte[TAMANHO_BUFFER];

    int ofs = ((int)inputFile.length());
    int fs = ofs;
    char pfs = ' ';

    if (fs >= 1000) {
      fs /= 1000;
      pfs = 'K';
      if (fs >= 1000) {
        fs /= 1000;
        pfs = 'M';
        if (fs >= 1000) {
          fs /= 1000;
          pfs = 'G';
        }
      }
    }   

    try {      

      for (TAMANHO_BUFFER += 0; TAMANHO_BUFFER >= 4; TAMANHO_BUFFER *= .5) {

        long startTime = System.currentTimeMillis();

        inputStream = new FileInputStream(inputFile);
        outputStream = new FileOutputStream(outputFile);

        int bytesRead;

        while ((bytesRead = inputStream.read(buffer)) != -1) {
          outputStream.write(buffer, 0, bytesRead);
        }

        long endTime = System.currentTimeMillis();
        
        float elapsedTime = (float)((endTime - startTime) / 1000.0);

        System.out.println( "\nNome do arquivo:    " + inputFile + 
                              "\nTamanho do arquivo: " + ofs + " Bytes " + '(' + fs + ' ' + pfs + 'B' + ')' + 
                              "\nTempo de execucao:  " + elapsedTime + " segundos" + 
                              "\nTamanho do buffer:  " + TAMANHO_BUFFER + " Bytes\n");

          writer.write( "\nNome do arquivo:" + inputFile + 
                        "\nTamanho do arquivo:" + ofs + " Bytes " + '(' + fs + ' ' + pfs + 'B' + ')' + 
                        "\nTempo de execucao:" + elapsedTime + " segundos" + 
                        "\nTamanho do buffer:" + TAMANHO_BUFFER + " Bytes\n");
          writer.flush();

        buffer = new byte[TAMANHO_BUFFER];

      } writer.close();
    } catch (IOException e) {
      System.out.println("An error occurred.");
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
