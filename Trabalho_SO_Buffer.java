import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

public class Trabalho_SO_Buffer {

  public static void main(String[] args)throws IOException {

    Scanner sc = new Scanner(System. in);

    InputStream inputStream = null;
    OutputStream outputStream = null;

    System.out.print("Arquivo de entrada: ");
    String inputFileName = sc.nextLine();
    if (inputFileName.isEmpty()){
      inputFileName = "video";
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

    
    String outputFile = inputFileName+".txt";
    System.out.print("Arquivo de saída: "+ outputFile);

    sc.close();

    int TAMANHO_BUFFER = 8192;
    byte[] buffer = new byte[TAMANHO_BUFFER];

    int ofs = ((int)inputFile.length());
    int fs = ofs;
    char pfs = ' ';

    for (TAMANHO_BUFFER += 0; TAMANHO_BUFFER >= 4; TAMANHO_BUFFER *= .5) {

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

      long startTime = System.currentTimeMillis();

      try {
        inputStream = new FileInputStream(inputFile);
        outputStream = new FileOutputStream(outputFile);

        int bytesRead;
        while ((bytesRead = inputStream.read(buffer)) != -1) {
          outputStream.write(buffer, 0, bytesRead);
        }

        float elapsedTime = (float)((System.currentTimeMillis() - startTime) / 1000.0);

        System.out.println( "\nNome do arquivo:    " + inputFile + 
                            "\nTamanho do arquivo: " + ofs + " Bytes " + '(' + fs + ' ' + pfs + 'B' + ')' + 
                            "\nTempo de execucao:  " + elapsedTime + " segundos" + 
                            "\nTamanho do buffer:  " + TAMANHO_BUFFER + " Bytes\n");

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
}