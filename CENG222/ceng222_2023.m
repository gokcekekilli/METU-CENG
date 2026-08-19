N = 1503;
lambdaB = 50;
lambdaC = 40;
lambdaD = 25;
TotalWeight = zeros(N,1);
for k = 1:N
  numB = 0;
  p = exp(-lambdaB);
  F = p;
  U = rand;
  while (U>F)
    numB = numB + 1;
    p = p*lambdaB/numB;
    F = F + p;
  end
  numC = 0;
  p = exp(-lambdaC);
  F = p;
  U = rand;
  while (U>F)
    numC = numC + 1;
    p = p*lambdaC/numC;
    F = F+p;
  end
  numD = 0;
  p = exp(-lambdaD);
  F = p;
  U = rand;
  while (U>F)
    numD = numD + 1;
    p = p*lambdaD/numD;
    F = F+p;
  end
  weightB = 0;
  for i = 1:numB
    X_gamma = 0;
    for j = 1:60
      X_gamma = X_gamma + (-1/0.1)*log(rand);
    end
    weightB = weightB + X_gamma;
  end
  weightC = 0;
  for i = 1:numC
    X_gamma = 0;
    for j = 1:100
      X_gamma = X_gamma + (-1/0.05)*log(rand);
    end
    weightC = weightC + X_gamma;
  end
  weightD = 0;
  for i = 1:numD
    X_gamma = 0;
    for j = 1:120
      X_gamma = X_gamma + (-1/0.02)*log(rand);
    end
    weightD = weightD + X_gamma;
  end
  TotalWeight(k) = weightB + weightC + weightD;
end
p_est = mean(TotalWeight > 300000);
expected_weight = mean(TotalWeight);
std_weight = std(TotalWeight);
fprintf('Estimated probability = %f\n', p_est);
fprintf('Expected weight = %f\n', expected_weight);
fprintf('Standard deviation = %f\n', std_weight);

