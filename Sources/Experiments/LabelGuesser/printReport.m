

function varargout = printReport(filename)

    rep = readReport(filename);
    testname = regexprep(filename, '.+/','');
    disp('======================================================');
    disp(testname)
    disp(['Area = ', num2str(100 - 100*sum(rep.posicoes) / (max(rep.posicoes) * max(size(rep.posicoes))) ), '%']);
    disp(['mean = ', num2str(mean(rep.posicoes))]);
    disp(['std  = ', num2str(std(rep.posicoes))]);
    disp(['not identified  = ', num2str( (100 - max(size(rep.posicoes) / max(size(rep.posicaoRankCorreto)))*100 )), '%']);
    if nargout == 0
        plot(sort(rep.posicoes));
        ylabel('Posicao em que o no correto estava')
        xlabel('Caso de teste')
    else
        varargout(1) = {rep};
    end
        
    disp('======================================================');
    n = 30;
    disp([num2str(n), ' Most erroneous classifications']);
    [a b] = sort(rep.posicaoRankCorreto, 'descend');
    disp('Hidden                      Rank              List Top 10 First Guesses')
    for i=1:n
       disp([rep.Escondido(b(i),:), '  ', num2str(rep.posicaoRankCorreto(b(i))) ,'  ', rep.Top10Escolhidos(b(i),:)])
    end
    
end



%repMult2 = readReport('/tmp/Implementation-Build/bin/guess_70p_2w_Mult.txt');



%repXor1 = readReport('/tmp/Implementation-Build/bin/guess_70p_1w_Xor.txt');
%repXor2 = readReport('/tmp/Implementation-Build/bin/guess_70p_2w_Xor.txt');

