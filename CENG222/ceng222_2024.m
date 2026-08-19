N = 4148;
lambdaA = 60;
lambdaT = 12;
alphaA = 120;
gamma_lambdaA = 0.1;
gamma_lambdaT = 0.001;
alphaT = 14;
threshold = 250000;
TotalWeight = zeros(N,1);
for k = 1:N
  numA = 0;
  p = exp(-lambdaA);
  F = p;
  U = rand;
  while (U > F)
    numA = numA+1;
    p = p*lambdaA/numA;
    F = F + p;
  end
  numT = 0;
  p = exp(-lambdaI);
  F = p;
  U = rand;
  while (U > F)
    numT = numT + 1;
    p = p* lambdaT/numT;
    F = F + p;
  end
  weightA = 0;
  for i = 1:numA
    X_gamma = 0;
    for j = 1:alphaA
      X_gamma = X_gamma + (1/gamma_lambdaA)*log(rand);
    end
    weightA = weightA + X_gamma;
  end
  weightT = 0;
  for i = 1:numT
    X_gamma = 0;
    for j = 1:alphaT
      X_gamma = X_gamma + (-1/gamma_lambdaT)*log(rand);
    end
    weightT = weightT + X_gamma;
  end
  TotalWeight(k) = weightA + weightT;
end
p_est = mean(TotalWeight > threshold);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);
optimalLambda = lambdaT;
for test_lambdaT = lambdaT:-0.1:0
    test_TotalWeight = zeros(N, 1);
    for k = 1:N
        numA = 0;
        p = exp(-lambdaA);
        F = p;
        U = rand;
        while (U > F)
          numA = numA+1;
          p = p*lambdaA/numA;
          F = F + p;
        end
        numT = 0;
        p = exp(-test_lambdaT);
        F = p;
        U = rand;
        while (U > F)
          numT = numT + 1;
          p = p* test_lambdaT/numT;
          F = F + p;
        end
        weightA = 0;
        for i = 1:numA
          X_gamma = 0;
          for j = 1:alphaA
            X_gamma = X_gamma + (1/gamma_lambdaA)*log(rand);
          end
          weightA = weightA + X_gamma;
        end
        weightT = 0;
        for i = 1:numT
          X_gamma = 0;
          for j = 1:alphaT
            X_gamma = X_gamma + (-1/gamma_lambdaT)*log(rand);
          end
          weightT = weightT + X_gamma;
        end
        test_TotalWeight(k) = weightA + weightT;
    end
    test_p_collapse = mean(test_TotalWeight > threshold);
    if test_p_collapse < 0.10
        optimal_lambdaT = test_lambdaT;
        break; % Şartı sağlayan en yüksek (ilk) değeri bulduğumuz için çıkıyoruz
    end
end
fprintf('Highest safe lambdaT limit (Risk < 10%%) = %f\n', optimal_lambdaT);
