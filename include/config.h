/***********************************************************************************
 *     Primera versión autómata serigrafía para Seritrade-
 * by Chema'22 v0.6RC
 * 
 * dos variadores de frecuencia 
 * VF1 pequeño (1HP) mueve delante detrás
 * con D2 enciendo o apago VF1 (por relé)                               K1 (blanco)
 * con D4 selecciono dirección (por relé)                               K2 (gris)
 * con D6 cambio potenciómetro de velocidad (impresión/entintado)       K3 (lila)
 * FALTARÍA gestionar si VF1 está ok o no...
 * 
 * VF2 grande (2HP) mueve arriba abajo
 * con D8 enciendo/apago VF2                                            K4 (Azul)
 * con D10 selecciono dirección                                         K5 (verde)
 * 
 * D3 esta a gnd si no está activado (final de carrera arriba VF2)      [1]
 * D5 esta a gnd si no está activado (final de carrera abajo VF2)       [2]
 * 
 * D7 esta a gnd si no está activado (final de carrera delante VF1)     [3]
 * D9 esta a gnd si no está activado (final de carrera detrás VF1)      [4]
 * 
 * D11 activa por relé un juego de válvulas de aire (1)                 K6 (amarillo)
 * D12 activa por relé un juego de válvulas de aire (2)                 K7 (naranja)
 * 
 * libre K8 (rojo)
 * Vcc K (marrón)
 * Gnd K (negro)
 * 
 * A0 se pone en gnd al pulsar el pedal de inicio maniobra              [0]
 * 
 * A1 se pone a gnd al pulsar el botón de flechas horizontales          [10]
 * A3 se pone a gnd al pulsar el botón de flechas verticales            [6]
 * A2 se pone a gnd al activar botón limpieza                           [    ]
 * 
 * ********************************************************************************/

#define activa LOW
#define apaga HIGH

#define DEBUG false              //para mandar más o menos mensajes por Serial

#define VF1p 2  //2             [K1]
#define VF1dir 4 //8            [K2]
#define VF1speed 6 //13         [K3]
#define VF1 true
#define VF2 false

#define VF2p 8 //7              [K4]
#define VF2dir 10 //9           [K5]

#define endup 5 //6             [2]
#define enddown 3 //5           [1]

#define endfront 7 //10         [3]
#define endback 9 //11          [4]

#define air1 11 //3             [K6]
#define air2 12 //12            [K7]

#define pedal A0 //4            [0]
#define lbutt A2 //A2           [ ]
#define horz A1 //A0            [10]
#define vert A3 //A1            [6]
#define semibutt A4  //         [ ]

#define TOFRONT true
#define TOBACK false

#define TOUP true
#define TODOWN false

#define RECOGER true
#define PRINTAR false

#define PALANTE 3
#define PATRAS 4
#define PARRIBA 2
#define PABAJO 1
#define PARADO 0

#define DELANTE_ABAJO 3
#define DELANTE_ARRIBA 2
#define ATRAS_ARRIBA 0
#define ATRAS_ABAJO 1

#define PAUSA 1000 //cuanto pausa al llegar arriba desde impresión ms
