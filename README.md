# InsTimeMachine
## Interactive Art project

### Limbo - limbo - L i m b o - LIMBO - LLIIMMBBOO - lliimmbboo - l1mb0
##          Daniela Palumbo
##        Diogo Teles Sant’Anna
##    Gabriel Pellegrino da Silva
##  Luciano Leite Fabris
##Maria Angélica Paulino Alves

### Documentação do Projeto Final - Manivela

#### Arquitetura:

A figura 1 a seguir contém o esquemático do hardware do projeto em uma protoboard, utilizado para testes iniciais e desenvolvimento do software presente no arduíno.

##### Figura 1: Esquemático do hardware do projeto
    
O esquemático apresentado contém 1 ESP8266 NodeMCU 1.0 Microcontroller, 1 Acelerômetro & Giroscópio (MPU-6050) e 1 motor vibrador flat para arduíno. O último foi representado como um servo motor pelo fato de não possuir templates no programa Fritzing (utilizado para criação da imagem), porém as suas ligações com o restante do circuito são equivalentes. Além dos componentes apresentados anteriormente, utilizou-se um power bank para alimentação do arduino. Por motivos de espaço, na versão final do projeto o circuito foi passado para duas placas universais perfuradas, uma contendo o arduino e outra com os demais periféricos.

- O programa presente no arduino consiste em:
  - Inicializar a comunicação Wi-Fi e com o shiftr.io (plataforma descrita a seguir), assim como presente no exemplo de comunicação contido no Pincello;
  - Realizar a leitura das informações vindas do MPU6050 (como descrito em https://www.filipeflop.com/blog/acelerometro-com-esp8266-nodemcu/);
  - Enviar a informação do eixo X do giroscópio para o shiftr.io, e receber deste a informação de vibração da manivela.

Para construção da interface gráfica foi utilizado o framework Qt e a linguagem C++. Qt é um framework já estabelecido no mercado de interfaces gráficas para aplicações desktop, possuindo diversas capacidades que atendiam as necessidades do projetos como fácil utilização, módulo de renderização 3D, áudio e conectividade com internet. Além disso, o mesmo já era familiar para alguns dos integrantes do grupo facilitando a sua utilização. Os módulos do framework utilizados para criação da interface foram: 

- Qt3D: para renderização do planeta terra em seus períodos geológicos.
- QMqtt: para comunicação com a plataforma Shiftr.io.
- QtMultimedia: para reprodução dos áudio para cada evento.
- Widgets: para organização de componentes da interface.

Os eventos históricos foram selecionados e salvos em arquivos de texto formatados utilizando a linguagem de marcação HTML para uma melhor organização e padronização do conteúdo. Além disso, todos os textos foram convertidos para arquivos de áudio de forma a melhorar a experiência de usuários de capacidades visuais reduzidas. Com estes dois meios como principais conteúdos, e utilizando o framework, foi feita a estruturação da interface gráfica e comunicação com a plataforma online como entrada da interação do usuário. 

##### Figura 2: Interface gráfica construída utilizando o framework Qt

Para comunicação entre a placa e a interface gráfica, utilizou-se a plataforma Shiftr.io. Com esta plataforma foi possível utilizar a funcionalidade de wi-fi do microcontroller para enviar dados para a nuvem, os quais eram redirecionados pela plataforma Shiftr para a interface gráfica que recebia e respondia aos dados dos sensores. Além disso, a interface gráfica também se comunicava com o dispositivo de vibração informando quando o usuário havia encontrado um evento histórico. O esquema abaixo ilustra a comunicação.

##### Figura 3: Ilustração do processo de comunicação do artefato

#### Modelo de Interação (artefato para o usuário):

##### Figura 4: Representação 3D do projeto em uma espaço interativo

O usuário inicia a interação frente a uma manivela e uma tela (figura 2) na qual ele pode observar o planeta terra girando, uma extensa linha do tempo e um breve texto descrevendo os dias atuais da humanidade, que logo começa a ser lido por uma voz automática.
    
A manivela é disposta em uma mesa com abertura embaixo para proporcionar uma maior acessibilidade direcionada a cadeirantes - uma cadeira também é disposta no local para possibilitar a interação sentada a pessoas não cadeirantes. A acessibilidade também foi abordada na implementação de leituras automáticas dos textos dispostos na tela, iniciada cada vez que o texto é alterado.

Dada a disposição dos objetos no ambiente espera-se que o usuário, movido pela curiosidade e intuição, comece a girar a manivela e perceba os diferentes outputs do artefato: uma suave movimentação na linha do tempo que quase imediatamente levará a uma sensível vibração na manivela, que o usuário deve relacionar a um novo evento encontrado indicado pela simultânea mudança do texto na tela, que logo começa a ser lido. 

O texto agora descreve uma época há aproximadamente 30 anos atrás, na intenção de remeter o usuário a uma época próxima à vivida por seus pais. Movendo mais um pouco a manivela, o usuário receberá os mesmos estímulos, voltará um pouco mais no tempo e terá uma descrição do tempo aproximadamente 80 anos atrás, época vivida por seus avós.

A interação continua seguindo esse raciocínio, com o objetivo de provocar o usuário o fazendo girar cada vez mais a manivela para encontrar um novo evento, o levando a épocas cada vez mais remotas na tentativa de desconstruir cada sentimento de antiguidade ao mostrar uma tempo ainda mais antigo, o convidando sempre a imaginar épocas cada vez mais remotas, apresentando o conceito de deep time.

Em determinados pontos da linha do tempo o usuário deve se deparar também com grandes mudanças na superfície do planeta terra exposto na tela. As transições entre a era glacial e a formação atual da terra, por exemplo, são perceptíveis pela animação.

O artefato deve ser capaz de transportar o usuário através de diferentes épocas, desde o dia atual ao surgimento do planeta que hoje chamamos de Terra, evento que para ser alcançado o usuário deve passar por muitos eventos, girando a manivela por muito tempo, o que também serve para exemplificar o deep time.

#### Processo de Design:

O design do projeto final começou a ser trabalhado em sala de aula com as atividades de brainwriting. No entanto, por conta da dificuldade do grupo em firmar as estruturas principais do projeto, algumas features adicionais tiveram de ser removidas do design para simplificar a execução e ser possível entregar o projeto a tempo.

A ideia inicial do projeto seria associar o movimento de uma manivela à reprodução de um vídeo. No entanto, não encontramos uma manivela boa o suficiente para representar a nossa ideia, e optamos por usar o pedal de uma bicicleta para suprir essa necessidade. A estrutura inicial seria assim:

##### Figura 5: estrutura inicial da manivela

Após conseguirmos a estrutura, outro desafio de design foi prendê-la de modo que ela pudesse girar e fosse confortável para o usuário. Para isso, decidimos mantê-la na horizontal, pois não forçaria tanto o ombro da pessoa que estivesse utilizando e também não causaria tantas variações no sensor de acelerômetro se a pessoa soltasse o pedal. Para melhorar a comunicação de um usuário com o artefato, colocamos palitos de churrasco no encaixe da manivela na bicicleta e enrolamos esses palitos com corda de varal para melhorar a sensação tátil.

Para possibilitar que todo o equipamento gire, todos os componentes envolvidos com o tratamento do sinal devem estar com a mesma velocidade angular, pois se não os fios irão enrolar e o artefato seria destruído com o uso. Foi preso com fita crepe um powerbank como fonte de bateria, o microcontrolador, os sensores e atuadores na manivela.

##### Figura 6: Manivela com os componentes anexados

Após isso, precisamos arrumar alguma estrutura que pudesse manter o pedal na posição desejada. Entre as opções consideradas tivemos a cimentação da base do pedal, utilização de um grampo (sargento) ou usar cordas para amarrá-lo. Apenas a última deu certo e foi a solução adotada pelo grupo para a entrega final. Devido a essa demora, tivemos que desconsiderar também uma representação mais visual do que poderia significar a manivela, que a princípio seria representada como um ponteiro de um relógio, que seria desenhado na base.

Ao longo do processo, algumas opções de design tiveram de ser abandonadas, entre elas as principais foram a presença de um botão para ativar a leitura de textos na tela. Essa opção foi desconsiderada pela dificuldade em fixar um botão na manivela de maneira funcional e que fosse ainda confortável para quem estivesse utilizando. Contudo, uma refatoração do projeto poderia contemplar essa feature facilmente, arrumando uma manivela maior ou reorganizando os objetos de modo a caber o botão.

No início, também eram previstas estruturas táteis com a intenção de tornar o manuseio mais acessível para pessoas com deficiências visuais. No entanto, essa etapa dependia da fixação da estrutura que prendia a manivela, a qual demorou a ficar pronta. A única opção tátil que foi possível manter foi o sensor de vibração, que acoplamos próximo a onde o usuário segura a manivela. A cada evento que se passa na tela, utilizamos o sensor para avisar ao usuário que algo mudou.

Quanto ao design da tela, mantivemos a ideia inicial de um vídeo mostrando os eventos históricos em um canto, uma representação do planeta dinâmica conforme a época do período histórico em que estamos; e também uma barra mostrando essa movimentação nos períodos da história da Terra.

Uma preocupação de design do grupo seria como pessoas cadeirantes poderiam fazer uso do artefato, e para tanto decidimos que o artefato deveria ser utilizado sentado, de modo que todos farão um uso equitativo nesse sentido. Outras considerações acerca de acessibilidade foram tomadas, além da vibração na manivela, como a audiodescrição do texto que aparece em cada evento.

##### Código do projeto: https://github.com/LucianoLeiteFabris/InsTimeMachine

