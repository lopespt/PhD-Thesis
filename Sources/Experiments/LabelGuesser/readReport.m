function saida = readReport( filename )
    %f = fopen(filename)
    
    %saida = textscan(f, '%d%q', 'Headerlines', 1)
    
    %fclose(f);

    saida = tdfread(filename, '\t');

    saida.posicoes = saida.posicaoRankCorreto;
    idx = saida.posicoes == -1;
    saida.posicoes(idx) = [];
    
end

