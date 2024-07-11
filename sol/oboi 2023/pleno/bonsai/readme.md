# Sol de Bonsai
Bonsai é uma arvore com vertices ponderados em que a beleza é a soma dos pesos. Consequentemente, subarvores tem belezas.<p>
Uma poda de um vertice é remover a subarvore, atualizando a beleza da arvore original.<p>
É possível realizar 0 até **k** podas. <p>

* 1 <= N <= 2e5
* 1 <= K <= min(N, 200)

Uma coisa que pensei na minha segunda tentativa de bonsai foi uma dp:

>**dp[u][j]** = bonsai ótima realizando **j** podas na subarvore de **v**.

mas pensar e implementar numa transição, mesmo com dfs, é praticamente impossível

Subarvore remete **euler tour**.
>**sp[ tout[u] ] - sp[ tin[u]-1 ]** = valor da subarvore **v**  
**tout[u]+1** = próximo vertice em euler tour

### A DP deve ser montada encima de **euler tour**

>**dp[ tin[u] ][j]** = bonsai ótima realizando **j** podas a partir da euler **v**.

#### long long DP[200010][210] inicializada em -inf
### Caso base
Se a partir da euler de **v** eu não realizo **nenhuma poda**, o resto do passeio fica intacto.
>**dp[ tin[u] ][0]** = resto do passeio: **sp[n] - sp[ tin[u]-1 ]**

### Transição
Se eu posso realizar **1** ou mais podas (**j>=1**), tenho que **escolher** entre **podar ou não podar** a subarvore atual, escolhendo o **máximo** entre as duas opções.  

#### O que acontece se eu **não podo**:<p>
- b[u] é incluso e me é permitido escolher ainda **j** podas a partir da primeira subarvore de v : 
    >*b[u]+dp[ tin[u]+1 ][j]*

#### O que acontece se eu **podo**:<p>
- toda subarvore de v **não** é inclusa e me é permitido escolher **j-1** podas depois da subarvore de v :
    >*dp[ tout[u]+1 ][j-1]*
#### Transição final
>**dp[ tin[u] ][j]** = max( b[u]+dp[ tin[u]+1 ][j] , dp[ tout[u]+1 ][j-1] )
#### Como implementar
A complexidade da dp é O(nk)=O(4*10^7), uma complexidade arriscada que excede o TL se for recursiva. É preciso de uma **dp iterativa**.<p>
* Pro estado tin[u] ser calculado, precisa ser calculado o estado tin[u]+1, sendo necessário uma **iteração decrescente**
* Iterar euler tour é simples e como se tem os termos u e tout[u] é preciso reverter a euler tour pra obter u.
* Como tin[u]<=tout[u], iterar decrescente funciona, mas deve se atentar quando forem iguais:
    >dp[ x ][j] = max( b[u]+dp[ x+1 ][j] , dp[ x+1 ][j-1] )

    é visível que para o estado j ser calculado, j-1 já deve ter sido calculado, necessitando de uma **iteração crescente**
#### Código da transição
```c++
for(int e=n; e>=1; e--){    //itera euler decrescente
    int u=et[e];            //reverte euler
    for(int j=1; j<=k; j++) //itera j crescente
        dp[e][j] = max( b[u]+dp[e+1][j] , dp[tout[u]+1][j-1] );
}
```


### Resposta
Posso realizar até **k** podas, então verifico todas as possibilidades de podas: **i: 0->k**
```c++
for(int i=0; i<=k; i++)
    ans=max(ans, dp[1][i]);
```
## Observação
**O(n * k)**, dado os limites, é uma complexidade arriscada pra **1s**, sendo a **constante alta** uma inimiga.

**Samuel Silva - 11.7.24.qui**
