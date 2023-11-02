import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.Scanner;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class teste {

    public static void main(String[] args) throws IOException {
        
    //try{

    Scanner sc = new Scanner(System.in);

    System.out.print("Arquivo de entrada (zip): ");
    String inputf = sc.next();
    if (!inputf.contains(".zip")){
        inputf = (inputf+".zip");
    }    
    
    System.out.print("Arquivo de saída (txt): ");
    String outputf = sc.next();
    if (!outputf.contains(".txt")){
        outputf = (outputf+".txt");
    }    

    sc.close();

        int TAMANHO_BUFFER = 8192;        
        byte[] buffer = new byte[TAMANHO_BUFFER];

        InputStream inputZip = null;
        OutputStream outputZip = null;

        ZipFile arquivoZip = new ZipFile(inputf);
        long fs = inputf.length();

        long startTime = System.currentTimeMillis();        
         System.out.println(startTime);
        for (TAMANHO_BUFFER+=0 ; TAMANHO_BUFFER >= 4; TAMANHO_BUFFER *= .5){
            
        arquivoZip = new ZipFile(inputf);

        Enumeration<? extends ZipEntry> entradas = arquivoZip.entries();

            buffer = new byte[TAMANHO_BUFFER];

            while(entradas.hasMoreElements()) {
                ZipEntry entrada = (ZipEntry) entradas.nextElement();
                
                inputZip = arquivoZip.getInputStream(entrada);
                outputZip = new FileOutputStream(outputf);
            
                int bytesLidos = 0;

                while((bytesLidos = inputZip.read(buffer)) > 0) {
                    outputZip.write(buffer, 0, bytesLidos);
                }

                inputZip.close();
                outputZip.close();

            }

            long elapsedTime = System.currentTimeMillis() - startTime;
            System.out.println(     "\nTamanho do arquivo:"+   fs               +"Bytes"               + '('+')'+
                                    "\nTempo de execução: "+   elapsedTime/1000      +"segundos"            +
                                    "\nTamanho do buffer: "+   TAMANHO_BUFFER   +"Bytes"+'('+')');

        arquivoZip.close();    
        }  

    }

    //catch (ZipException entradas){
       // throw entradas;
    //}
//}
}
