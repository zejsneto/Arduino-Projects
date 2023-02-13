// C++ code
//

/* Números em Morse */
int num1[] = {0, 1, 1, 1, 1}; // * - - - - = 1
int num2[] = {0, 0, 1, 1, 1}; // * * - - - = 2
int num3[] = {0, 0, 0, 1, 1}; // * * * - - = 3
int num4[] = {0, 0, 0, 0, 1}; // * * * * - = 4
int num5[] = {0, 0, 0, 0, 0}; // * * * * * = 5
int num6[] = {1, 0, 0, 0, 0}; // - * * * * = 6
int num7[] = {1, 1, 0, 0, 0}; // - - * * * = 7
int num8[] = {1, 1, 1, 0, 0}; // - - - * * = 8
int num9[] = {1, 1, 1, 1, 0}; // - - - - * = 9
int num0[] = {1, 1, 1, 1, 1}; // - - - - - = 0

/* Somas > 9 em Morse */
int num10[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int num11[] = {0, 1, 1, 1, 1, 0, 1, 1, 1, 1};
int num12[] = {0, 1, 1, 1, 1, 0, 0, 1, 1, 1};
int num13[] = {0, 1, 1, 1, 1, 0, 0, 0, 1, 1};
int num14[] = {0, 1, 1, 1, 1, 0, 0, 0, 0, 1};
int num15[] = {0, 1, 1, 1, 1, 0, 0, 0, 0, 0};
int num16[] = {0, 1, 1, 1, 1, 1, 0, 0, 0, 0};
int num17[] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 0};
int num18[] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 0};

/* Variáveis Auxiliares */
int deltaAux = 0;
int count = 0;
int aux = 0;
int var5 = 0;
int var10 = 0;
int iEnvia = 0;
int iRecebe = 0;

/* Variável Potenciômetro */
int potenciometro = 0;

/* Variáveis Tempo de Luz */
int f = 0;
int tempoSemLuz = 0;
int tempoComLuz = 0;
int deltaTempo = 0;

/* Variáveis Transforma e Armazena 0,1 -> Recebido[] */
int sum1 = 0;
int sum2 = -1;
int recebido1[5];
int recebido2[5];

/* Variáveis memcmp() e CalcSoma */
int recebidoInt1 = 0;
int recebidoInt2 = 0;
int soma = 0;

/* Variáveis RecebeSoma() */
int recebidoSoma1[5];
int recebidoSoma2[10];
int recebidoSomaInt;

/* Void Setup */
void setup()
{
    Serial.begin(9600);

    pinMode(13, OUTPUT); // LED DIREITA
    pinMode(12, OUTPUT); // LED ESQUERDA -> Envia
    pinMode(7, OUTPUT);  // LED PRINCIPAL -> Recebe
    pinMode(A0, INPUT);  // LDR
    pinMode(A1, INPUT);  // POTENCIOMETRO 0 - 1023
}

void loop()
{
    potenciometro = analogRead(A1);
    // Serial.println(potenciometro);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);

    /* ENVIA */
    if (potenciometro < 300)
    {
        /* ACENDE E APAGA LEDS SECUNDÁRIOS */
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);

        /* VERIFICA ORDEM MÉTODOS*/
        if (iEnvia == 0)
        {
            iEnvia++;
            envia(num2);
            Serial.println("Enviado num2");
            delay(2000);
        }
        if (iEnvia == 1)
        {
            iEnvia++;
            envia(num6);
            Serial.println("Enviado num6");
            delay(2000);
        }
        if (iEnvia == 2)
        {
            iEnvia++;
            recebeSoma();
            Serial.println("Soma recebida");
            Serial.println(recebidoSomaInt);
            delay(2000);
        }
    }

    /* RECEBE */
    else if (potenciometro > 800)
    {
        /* ACENDE E APAGA LEDS SECUNDÁRIOS */
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);

        /* MÉTODOS */
        if (iRecebe == 0)
        {
            iRecebe++;
            recebe();
            Serial.println("Recebido dois num");
            delay(2000);
        }
        if (iRecebe == 5)
        {
            iRecebe++;
            calcSoma();
            Serial.println("Soma calculada");
            Serial.println(soma);
            delay(2000);
        }

        if (iRecebe == 6)
        {
            iRecebe++;
            enviaSoma();
            Serial.println("Soma enviada");
            delay(2000);
        }
    }
} // fim void loop

void envia(int num[])
{
    for (int aux = 0; aux < 5; aux++)
    {
        if (num[aux] == 0)
        {
            digitalWrite(7, HIGH);
            delay(500);
            digitalWrite(7, LOW);
            delay(1000);
        }
        if (num[aux] == 1)
        {
            digitalWrite(7, HIGH);
            delay(1500);
            digitalWrite(7, LOW);
            delay(1000);
        }
    }
}

void recebe()
{
    while (true)
    {
        /* MÉTODO RECEBE 2 NUM POR MORSE */

        /* Quanto tempo recebeu Luz */

        // 160 = Intensidade de Luz com LED ligado
        if (analogRead(A0) < 160)
        {
            tempoSemLuz = f;
            tempoComLuz = millis();
        }
        // 170 = Intensidade de Luz com LED desligado
        else
        {
            f = millis();

            // Armazena tempo que recebeu luz */
            deltaTempo = tempoComLuz - tempoSemLuz;
            Serial.println("Delta tempo");
            Serial.println(deltaTempo);
            tempoSemLuz = 0;
            tempoComLuz = 0;
        }

        if (deltaTempo > 300 && deltaTempo < 1700)
        {
            /* Tranforma tempo em int */
            if (deltaTempo > 300 && deltaTempo < 600)
            {
                deltaTempo = 0;
            }
            else
            {
                deltaTempo = 1;
            }

            /* Adiciona em 2 vetores de tamanho [5] */

            if (sum1 < 4)
            {
                recebido1[sum1] = deltaTempo;
                Serial.println("add recebido1 na posicao");
                Serial.println(sum1);
                Serial.println(recebido1[sum1]);
                sum1++;
            }
            else if (sum1 == 4)
            {
                recebido1[sum1] = deltaTempo;
                Serial.println("add recebido1 na posicao");
                Serial.println(sum1);
                Serial.println(recebido1[sum1]);
                sum1++;
                sum2 = 0;
            }
            else if (sum2 >= 0 && sum2 < 5)
            {
                recebido2[sum2] = deltaTempo;
                Serial.println("add recebido2 na posicao");
                Serial.println(sum2);
                Serial.println(recebido2[sum2]);
                sum2++;
            }
        }

        if (sum2 >= 5)
        {
            iRecebe = 5;
            break;
        }
    }

} // fim recebe

void calcSoma()
{
    /* Compara os números recebidos com os vetores existentes (num0-num9) */

    /* Verifica recebido1 */

    if (memcmp(recebido1, num1, sizeof(num1)) == 0)
    {
        recebidoInt1 = 1;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num2, sizeof(num2)) == 0)
    {
        recebidoInt1 = 2;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num3, sizeof(num3)) == 0)
    {
        recebidoInt1 = 3;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num4, sizeof(num4)) == 0)
    {
        recebidoInt1 = 4;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num5, sizeof(num5)) == 0)
    {
        recebidoInt1 = 5;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num6, sizeof(num6)) == 0)
    {
        recebidoInt1 = 6;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num7, sizeof(num7)) == 0)
    {
        recebidoInt1 = 7;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num8, sizeof(num8)) == 0)
    {
        recebidoInt1 = 8;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num9, sizeof(num9)) == 0)
    {
        recebidoInt1 = 9;
        Serial.println(recebidoInt1);
    }
    else if (memcmp(recebido1, num0, sizeof(num0)) == 0)
    {
        recebidoInt1 = 0;
        Serial.println(recebidoInt1);
    }

    /* Verifica 2 */

    if (memcmp(recebido2, num1, sizeof(num1)) == 0)
    {
        recebidoInt2 = 1;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num2, sizeof(num2)) == 0)
    {
        recebidoInt2 = 2;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num3, sizeof(num3)) == 0)
    {
        recebidoInt2 = 3;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num4, sizeof(num4)) == 0)
    {
        recebidoInt2 = 4;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num5, sizeof(num5)) == 0)
    {
        recebidoInt2 = 5;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num6, sizeof(num6)) == 0)
    {
        recebidoInt2 = 6;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num7, sizeof(num7)) == 0)
    {
        recebidoInt2 = 7;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num8, sizeof(num8)) == 0)
    {
        recebidoInt2 = 8;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num9, sizeof(num9)) == 0)
    {
        recebidoInt2 = 9;
        Serial.println(recebidoInt2);
    }
    else if (memcmp(recebido2, num0, sizeof(num0)) == 0)
    {
        recebidoInt2 = 0;
        Serial.println(recebidoInt2);
    }

    soma = recebidoInt1 + recebidoInt2;
    Serial.println(soma);
} // fim calcSoma()

void enviaSoma()
{
    /* 0 - 9 */
    if (soma == 0)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num0[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num0[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 1)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num1[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num1[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 2)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num2[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num2[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 3)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num3[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num3[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 4)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num4[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num4[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 5)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num5[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num5[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 6)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num6[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num6[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 7)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num7[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num7[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 8)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num8[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num8[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 9)
    {
        for (int count = 0; count < 5; count++)
        {
            if (num9[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num9[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    /* 10 - 18 */
    if (soma == 10)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num10[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num10[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 11)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num11[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num11[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 12)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num12[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num12[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 13)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num13[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num13[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 14)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num14[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num14[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 15)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num15[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num15[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 16)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num16[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num16[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 17)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num17[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num17[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

    if (soma == 18)
    {
        for (int count = 0; count < 10; count++)
        {
            if (num18[count] == 0)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("0");
            }
            if (num18[count] == 1)
            {
                /* Acende LED */
                digitalWrite(7, HIGH);
                /* Apaga LED */
                delay(1500);
                digitalWrite(7, LOW);
                delay(1000);
                // Serial.println("1");
            }
        }
    }

} // fim enviaSoma()

void recebeSoma()
{
    while (true)
    {

        /* Quanto tempo recebeu Luz */

        // 160 = Intensidade de Luz com LED ligado
        if (analogRead(A0) < 160)
        {
            tempoSemLuz = f;
            tempoComLuz = millis();
        }
        // 170 = Intensidade de Luz com LED desligado
        else
        {
            f = millis();

            // Armazena tempo que recebeu luz */
            deltaTempo = tempoComLuz - tempoSemLuz;
            Serial.println("Delta tempo recebeSoma");
            Serial.println(deltaTempo);
            tempoSemLuz = 0;
            tempoComLuz = 0;
        }

        if (deltaTempo > 300 && deltaTempo < 1700)
        {
            /* Tranforma tempo em int */
            if (deltaTempo > 300 && deltaTempo < 600)
            {
                deltaTempo = 0;
            }
            else
            {
                deltaTempo = 1;
            }

            /* Adiciona em 2 vetores de tamanho [5] e tamanho [10] */

            if (var5 < 5)
            {
                recebidoSoma1[var5] = deltaTempo;
                Serial.println(recebidoSoma1[var5]);
                var5++;
            }
            if (var10 < 10)
            {
                recebidoSoma2[var10] = deltaTempo;
                Serial.println(recebidoSoma2[var10]);
                var10++;
            }

            if (var5 >= 5)
            {
                if (memcmp(recebidoSoma1, num0, sizeof(num0)) == 0)
                {
                    recebidoSomaInt = 0;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                if (memcmp(recebidoSoma1, num1, sizeof(num1)) == 0)
                {
                    recebidoSomaInt = 1;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num2, sizeof(num2)) == 0)
                {
                    recebidoSomaInt = 2;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num3, sizeof(num3)) == 0)
                {
                    recebidoSomaInt = 3;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num4, sizeof(num4)) == 0)
                {
                    recebidoSomaInt = 4;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num5, sizeof(num5)) == 0)
                {
                    recebidoSomaInt = 5;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num6, sizeof(num6)) == 0)
                {
                    recebidoSomaInt = 6;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num7, sizeof(num7)) == 0)
                {
                    recebidoSomaInt = 7;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num8, sizeof(num8)) == 0)
                {
                    recebidoSomaInt = 8;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma1, num9, sizeof(num9)) == 0)
                {
                    recebidoSomaInt = 9;
                    Serial.println(recebidoSomaInt);
                    break;
                }
            }
            if (var10 >= 10)
            {
                if (memcmp(recebidoSoma2, num10, sizeof(num10)) == 0)
                {
                    recebidoSomaInt = 10;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num11, sizeof(num11)) == 0)
                {
                    recebidoSomaInt = 11;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num12, sizeof(num12)) == 0)
                {
                    recebidoSomaInt = 12;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num13, sizeof(num13)) == 0)
                {
                    recebidoSomaInt = 13;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num14, sizeof(num14)) == 0)
                {
                    recebidoSomaInt = 14;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num15, sizeof(num15)) == 0)
                {
                    recebidoSomaInt = 15;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num16, sizeof(num16)) == 0)
                {
                    recebidoSomaInt = 16;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num17, sizeof(num17)) == 0)
                {
                    recebidoSomaInt = 17;
                    Serial.println(recebidoSomaInt);
                    break;
                }
                else if (memcmp(recebidoSoma2, num18, sizeof(num18)) == 0)
                {
                    recebidoSomaInt = 18;
                    Serial.println(recebidoSomaInt);
                    break;
                }
            }
            
        }
    }
}
