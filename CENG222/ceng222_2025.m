N = 4148;
lambdaS = 40;  % number of students
lambdaI = 15;  % number of instructors
lambdaE = 5;  % number of entrepreneurs

TotalMoney = zeros(N,1); % a vector that keeps the total money spent for each Monte Carlo run

for k = 1:N;
  % first generate the number of customers for each type from Poisson
  numS = 0;
  p=exp(-lambdaS);
  F = p;
  U = rand;
  while (U > F)
    numS = numS + 1;
    p = p*lambdaS/numS;
    F = F + p;
  end

  numI = 0;
  p = exp(-lambdaI);
  F = p;
  U = rand;
  while (U > F)
    numI = numI + 1;
    p = p*lambdaI/numI;
    F = F + p;
  end;

  numE = 0;
  p = exp(-lambdaE);
  F = p;
  U = rand;
  while (U > F)
    numE = numE + 1;
    p = p*lambdaE/numE;
    F = F + p;
  end
  moneyS = 0;
  for i = 1 : numS
    X_gamma = 0;
   for j = 1 : 15
     X_gamma = X_gamma + (-1/0.15) * log(rand);
   end
   moneyS = moneyS + X_gamma;
  end
  moneyI = 0;
  for i = 1 : numI
    X_gamma = 0;
    for j = 1:8
      X_gamma = X_gamma + (-1/0.05)*log(rand);
    end
    moneyI = moneyI + X_gamma;
  end
  moneyE = 0;
  for i = 1:numE
    U1 = rand;
    U2 = rand;
    Z = sqrt(-2 * log(U1)) * cos(2 * pi * U2);
    moneyE = moneyE + (400 + 50 * Z);
  end

  %moneyE = sum(400+50*randn(numE,1));


  TotalMoney(k) = moneyS + moneyI + moneyE;
end;
p_est = mean(TotalMoney >= 9000) ;
expectedMoney = mean(TotalMoney);
stdMoney = std(TotalMoney);

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected money = %f\n',expectedMoney);
fprintf('Standard deviation = %f\n',stdMoney);

% %90 Başarı için en yüksek yeni eşiğin bulunması (Percentile Yöntemi)
sorted_money = sort(TotalMoney);
new_threshold_index = round(0.10 * N); % Günlerin %10'u bu eşiğin altında kalmalı
recommended_threshold = sorted_money(new_threshold_index);
