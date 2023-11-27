program Trabalho_SO_Buffer_Delphi;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  SysUtils, Classes, Windows;

var
  inputStream: TFileStream;
  outputStream: TFileStream;
  writer: TStreamWriter;
  inputFileName, outputFile: string;
  TAMANHO_BUFFER, bytesRead,ofs, fs: Integer;
  buffer: array of Byte;
  pfs: Char;
  startTime, elapsedTime: Double;
  fileStream: TFileStream;

begin
  try
    Write('Arquivo de entrada (0 para valor padr�o): ');
    ReadLn(inputFileName);

    if inputFileName = '0' then
      inputFileName := 'video.mp4';

    outputFile := '.\outputs\delphi\' + ExtractFileName(inputFileName) + '.txt';

    TAMANHO_BUFFER := 32768;
    SetLength(buffer, TAMANHO_BUFFER);

    fileStream := TFileStream.Create(inputFileName, fmOpenRead or fmShareDenyNone);
    try
      ofs := fileStream.Size;
    finally
      fileStream.Free;
    end;

    fs := ofs;
    pfs := ' ';

    if fs >= 1000 then
    begin
      fs := fs div 1000;
      pfs := 'K';
      if fs >= 1000 then
      begin
        fs := fs div 1000;
        pfs := 'M';
        if fs >= 1000 then
        begin
          fs := fs div 1000;
          pfs := 'G';
        end;
      end;
    end;

    while (TAMANHO_BUFFER >= 4) do
    begin
      startTime := GetTickCount;

      inputStream := TFileStream.Create(inputFileName, fmOpenRead or fmShareDenyNone);
      outputStream := TFileStream.Create(outputFile, fmCreate or fmShareDenyNone);

      repeat
        SetLength(buffer, TAMANHO_BUFFER);
        bytesRead := inputStream.Read(buffer[0], Length(buffer));
        outputStream.WriteBuffer(buffer[0], bytesRead);
      until bytesRead = 0;

      elapsedTime := (GetTickCount - startTime) / 1000;

      WriteLn(Format(
        'Nome do arquivo:    %s'#13#10 +
        'Tamanho do arquivo: %d Bytes (%d %sB)'#13#10 +
        'Tempo de execucao:  %.3f segundos'#13#10 +
        'Tamanho do buffer:  %d Bytes'#13#10,
        [inputFileName, ofs, fs, pfs, elapsedTime, TAMANHO_BUFFER]
      ));

      writer := TStreamWriter.Create('log.txt', True);
      try
        writer.Write(Format(
          'Nome do arquivo:    %s'#13#10 +
          'Tamanho do arquivo: %d Bytes (%d %sB)'#13#10 +
          'Tempo de execucao:  %.3f segundos'#13#10 +
          'Tamanho do buffer:  %d Bytes'#13#10,
          [inputFileName, ofs, fs, pfs, elapsedTime, TAMANHO_BUFFER]
        ));
        writer.Flush;
      finally
        FreeAndNil(writer);
      end;

       TAMANHO_BUFFER := TAMANHO_BUFFER div 2;
    end;
  except
    on E: Exception do
    begin
      WriteLn('An error occurred: ', E.Message);
    end;
  end;
end.
