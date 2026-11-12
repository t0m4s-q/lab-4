{
  "graph": {
    "cells": [
      {
        "position": {
          "x": 0,
          "y": 0
        },
        "size": {
          "height": 10,
          "width": 10
        },
        "type": "Statechart",
        "id": "_biM_oNctEfGRwJx1tbcBBg",
        "attrs": {
          "name": {
            "text": "Statechart Export"
          },
          "specification": {
            "text": "// Use the event driven execution model.\n// Switch to cycle based behavior\n// by specifying '@CycleBased(200)'.\n@EventDriven\n\n// Use @SuperSteps(yes) to enable\n// super step semantics.\n@SuperSteps(no)\n\n\ninterface:\n\t// Define events and variables here. \n\t// Use CTRL + Space for content assist.\n\tin event myEvent\t\n\tin event startStop\n  in event modo\n  in event abrir\n  in event cerrar\n  var microondas_activo: boolean\n  var grill_activo: boolean\n  var ind_micro: boolean\n  var ind_grill: boolean\ninternal:\n  var vFuncionando: boolean=false\n  var hito4vFuncionando: boolean=false\n  \n  \n interface hito1:\n var led_encendido: boolean\n in event pulsacion \n  interface hito1b:\n var led_encendido1: boolean=false\n in event pulsacion1 \n  var led_encendido2: boolean =false\n in event pulsacion2 \n \n \n interface hito4:\n\t// Define events and variables here. \n\t// Use CTRL + Space for content assist.\n\tin event myEvent\t\n\tin event startStop\n  in event modo\n  in event abrir\n  in event cerrar\n  var microondas_activo: boolean\n  var grill_activo: boolean\n  var ind_micro: boolean\n  var ind_grill: boolean\n  var aviso_activo: boolean\n"
          }
        },
        "z": 0
      },
      {
        "position": {
          "x": 971,
          "y": 41
        },
        "size": {
          "width": 945,
          "height": 768
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          },
          "name": {
            "text": "r_modo"
          }
        },
        "embeds": [
          "_hx8YANcwEfGRwJx1tbcBBg",
          "_uTvrsNcwEfGRwJx1tbcBBg",
          "91a891c5-9e37-4429-b783-a807774a8db1",
          "_OC1wINcwEfGRwJx1tbcBBg",
          "fac6818c-22bb-4401-b141-c39d3e67d26b",
          "_YO4tYNcwEfGRwJx1tbcBBg"
        ],
        "id": "_rcU6ANctEfGRwJx1tbcBBg",
        "z": 1159
      },
      {
        "position": {
          "x": 1038,
          "y": 94
        },
        "size": {
          "height": 93,
          "width": 212
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "microondas",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/ ind_micro=true; ind_grill=false\r\n"
          }
        },
        "embeds": [],
        "id": "_OC1wINcwEfGRwJx1tbcBBg",
        "parent": "_rcU6ANctEfGRwJx1tbcBBg",
        "z": 1160
      },
      {
        "position": {
          "x": 1301,
          "y": 76
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "fac6818c-22bb-4401-b141-c39d3e67d26b",
        "z": 1161,
        "parent": "_rcU6ANctEfGRwJx1tbcBBg",
        "embeds": [
          "694144b0-050f-4471-924a-fe861154d72b"
        ]
      },
      {
        "position": {
          "x": 1012,
          "y": 326
        },
        "size": {
          "height": 91,
          "width": 227
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "grill",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/ ind_grill=true; ind_micro=false\r\n"
          }
        },
        "embeds": [],
        "id": "_YO4tYNcwEfGRwJx1tbcBBg",
        "z": 1163,
        "parent": "_rcU6ANctEfGRwJx1tbcBBg"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": 1301,
          "y": 91
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "694144b0-050f-4471-924a-fe861154d72b",
        "z": 1166,
        "parent": "fac6818c-22bb-4401-b141-c39d3e67d26b"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "fac6818c-22bb-4401-b141-c39d3e67d26b"
        },
        "target": {
          "id": "_OC1wINcwEfGRwJx1tbcBBg",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "51.887%",
              "dy": "47.312%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "91a891c5-9e37-4429-b783-a807774a8db1",
        "z": 1167,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "_rcU6ANctEfGRwJx1tbcBBg"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_YO4tYNcwEfGRwJx1tbcBBg",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "96.667%",
              "dy": "2.655%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "_OC1wINcwEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "modo [!vFuncionando]"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "_uTvrsNcwEfGRwJx1tbcBBg",
        "parent": "_rcU6ANctEfGRwJx1tbcBBg",
        "z": 1167
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_OC1wINcwEfGRwJx1tbcBBg",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "6.132%",
              "dy": "98.925%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "_YO4tYNcwEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "modo [!vFuncionando]"
              }
            },
            "position": {
              "distance": 0.5078740157480315,
              "offset": -23,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "_hx8YANcwEfGRwJx1tbcBBg",
        "parent": "_rcU6ANctEfGRwJx1tbcBBg",
        "z": 1167
      },
      {
        "position": {
          "x": 480,
          "y": 1455
        },
        "size": {
          "width": 1396,
          "height": 406
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 3
          },
          "name": {
            "text": "hito1b"
          }
        },
        "id": "dcd4eed6-0bf7-44d3-a64f-1109881f8821",
        "z": 1386,
        "embeds": [
          "a269a49c-2ad5-4766-bc5d-3f3db80c7534",
          "07cb4608-988c-4c19-92a0-eb25b34abe36",
          "81567dcf-dfff-4a17-b869-f803c702733c",
          "364705e2-7900-4efb-92b9-2036192fc267",
          "c75e4297-3dab-41bc-875a-32316c76d269",
          "00d95e9c-f253-4578-81c8-525a35aa7435",
          "ff65e0b0-c81d-40c2-82a3-a050827db124",
          "7a53dfae-b893-42c3-b833-4063251f411f"
        ]
      },
      {
        "position": {
          "x": 583,
          "y": 1498
        },
        "size": {
          "height": 243,
          "width": 179
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "led_encendido",
            "fontSize": 11
          }
        },
        "id": "00d95e9c-f253-4578-81c8-525a35aa7435",
        "z": 1387,
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821",
        "embeds": [
          "b246b355-d7e6-468e-87da-b7bea711642e",
          "5984400c-a6bc-4136-a1fb-85de7101ea4c"
        ]
      },
      {
        "position": {
          "x": 1031,
          "y": 1475
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "ff65e0b0-c81d-40c2-82a3-a050827db124",
        "z": 1388,
        "embeds": [
          "e5b042b7-ae1c-420b-96f2-87a24926db68"
        ],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "position": {
          "x": 1240,
          "y": 1521
        },
        "size": {
          "height": 167,
          "width": 381
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "led_apagado",
            "fontSize": 11
          }
        },
        "id": "7a53dfae-b893-42c3-b833-4063251f411f",
        "z": 1389,
        "embeds": [
          "eb316956-97f2-421f-b5ca-29d04679588f",
          "6510f2e5-58b5-4d16-b996-59f4137313e6"
        ],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": 1031,
          "y": 1490
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "e5b042b7-ae1c-420b-96f2-87a24926db68",
        "z": 1397,
        "parent": "ff65e0b0-c81d-40c2-82a3-a050827db124"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "ff65e0b0-c81d-40c2-82a3-a050827db124"
        },
        "target": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "29.054%",
              "dy": "13.187%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "a269a49c-2ad5-4766-bc5d-3f3db80c7534",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f"
        },
        "target": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "100%",
              "dy": "45%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion2[hito1b.led_encendido2==false]/hito1b.led_encendido2=true"
              }
            },
            "position": {
              "offset": 14,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "364705e2-7900-4efb-92b9-2036192fc267",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f"
        },
        "target": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "100%",
              "dy": "56.061%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion1[hito1b.led_encendido1==false]/hito1b.led_encendido1=true"
              }
            },
            "position": {
              "distance": 0.5104166666666666,
              "offset": -18.000019531250018,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "c75e4297-3dab-41bc-875a-32316c76d269",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435"
        },
        "target": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "0%",
              "dy": "51.029%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion1[hito1b.led_encendido1==false]/hito1b.led_encendido1=true"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "4"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "b246b355-d7e6-468e-87da-b7bea711642e",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "00d95e9c-f253-4578-81c8-525a35aa7435"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435"
        },
        "target": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "52.514%",
              "dy": "91.358%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion2[hito1b.led_encendido2==false]/hito1b.led_encendido2=true"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "5984400c-a6bc-4136-a1fb-85de7101ea4c",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 664.5,
            "y": 1781
          }
        ],
        "parent": "00d95e9c-f253-4578-81c8-525a35aa7435"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435"
        },
        "target": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "2.703%",
              "dy": "36.264%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion2[hito1b.led_encendido2==true]/hito1b.led_encendido2=false"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "07cb4608-988c-4c19-92a0-eb25b34abe36",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "00d95e9c-f253-4578-81c8-525a35aa7435"
        },
        "target": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "0.676%",
              "dy": "5.495%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion1[hito1b.led_encendido1==true]/hito1b.led_encendido1=false"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "81567dcf-dfff-4a17-b869-f803c702733c",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "dcd4eed6-0bf7-44d3-a64f-1109881f8821"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f"
        },
        "target": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "98.688%",
              "dy": "54.491%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion2[hito1b.led_encendido2==true]/hito1b.led_encendido2=false"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "6510f2e5-58b5-4d16-b996-59f4137313e6",
        "z": 1398,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "7a53dfae-b893-42c3-b833-4063251f411f"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f"
        },
        "target": {
          "id": "7a53dfae-b893-42c3-b833-4063251f411f",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "16.273%",
              "dy": "94.012%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1b.pulsacion1[hito1b.led_encendido1==true]/hito1b.led_encendido1=false"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "4"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "eb316956-97f2-421f-b5ca-29d04679588f",
        "z": 1399,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "7a53dfae-b893-42c3-b833-4063251f411f"
      },
      {
        "position": {
          "x": -712,
          "y": 292
        },
        "size": {
          "width": 465,
          "height": 208
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 6
          },
          "name": {
            "text": "hito1"
          }
        },
        "id": "7b67682b-9be6-4ff7-bf69-0105f253e581",
        "z": 1402,
        "embeds": [
          "2e399be5-2b3f-482c-9447-e4b67a92aba4",
          "307770e5-8da0-42e9-a645-5a8ee327e18f",
          "048cb905-86d3-48be-be74-fcd270d801f8",
          "161c28f2-7c21-470c-b899-09619387cd10",
          "053637a3-ec6d-4fdd-9c2f-53088a89181c",
          "4a9da325-bd2f-4e74-9371-df489e247743"
        ]
      },
      {
        "position": {
          "x": -698,
          "y": 360
        },
        "size": {
          "height": 64,
          "width": 145
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "LED_ENCENDIDO",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/hito1.led_encendido=true"
          }
        },
        "id": "161c28f2-7c21-470c-b899-09619387cd10",
        "z": 1403,
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "position": {
          "x": -395,
          "y": 312
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "053637a3-ec6d-4fdd-9c2f-53088a89181c",
        "z": 1404,
        "embeds": [
          "7c4c6868-393f-479b-9f4b-706e9a51c1a3"
        ],
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "position": {
          "x": -483,
          "y": 364
        },
        "size": {
          "height": 76,
          "width": 158
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "LED_APAGADO",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/hito1.led_encendido=false"
          }
        },
        "id": "4a9da325-bd2f-4e74-9371-df489e247743",
        "z": 1405,
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -395,
          "y": 327
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "7c4c6868-393f-479b-9f4b-706e9a51c1a3",
        "z": 1409,
        "parent": "053637a3-ec6d-4fdd-9c2f-53088a89181c"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "053637a3-ec6d-4fdd-9c2f-53088a89181c"
        },
        "target": {
          "id": "4a9da325-bd2f-4e74-9371-df489e247743",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "50.633%",
              "dy": "9.211%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "307770e5-8da0-42e9-a645-5a8ee327e18f",
        "z": 1410,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "4a9da325-bd2f-4e74-9371-df489e247743"
        },
        "target": {
          "id": "161c28f2-7c21-470c-b899-09619387cd10",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "93.793%",
              "dy": "89.063%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1.pulsacion"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "048cb905-86d3-48be-be74-fcd270d801f8",
        "z": 1410,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "161c28f2-7c21-470c-b899-09619387cd10"
        },
        "target": {
          "id": "4a9da325-bd2f-4e74-9371-df489e247743",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "1.266%",
              "dy": "13.158%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito1.pulsacion\n"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "2e399be5-2b3f-482c-9447-e4b67a92aba4",
        "z": 1410,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "7b67682b-9be6-4ff7-bf69-0105f253e581"
      },
      {
        "position": {
          "x": 69,
          "y": 59
        },
        "size": {
          "width": 869,
          "height": 430
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 4
          },
          "name": {
            "text": "r_operacion"
          }
        },
        "embeds": [
          "3ed66e59-955a-4b35-9b68-70cac887f079",
          "_2md3MNctEfGRwJx1tbcBBg",
          "_JIRJANcvEfGRwJx1tbcBBg",
          "_AVbaYNcvEfGRwJx1tbcBBg",
          "_FcvScNcvEfGRwJx1tbcBBg",
          "_biQC9NctEfGRwJx1tbcBBg"
        ],
        "id": "_biQC89ctEfGRwJx1tbcBBg",
        "z": 1411
      },
      {
        "position": {
          "x": 72,
          "y": 124
        },
        "size": {
          "height": 236,
          "width": 822
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "puerta_cerrada",
            "fontSize": 11
          }
        },
        "embeds": [
          "_2meeQNctEfGRwJx1tbcBBg"
        ],
        "id": "_2md3MNctEfGRwJx1tbcBBg",
        "parent": "_biQC89ctEfGRwJx1tbcBBg",
        "z": 1412
      },
      {
        "position": {
          "x": 120,
          "y": 396
        },
        "size": {
          "height": 53,
          "width": 213
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "puerta_abierta",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/vFuncionando=false\r\n"
          }
        },
        "embeds": [],
        "id": "_AVbaYNcvEfGRwJx1tbcBBg",
        "parent": "_biQC89ctEfGRwJx1tbcBBg",
        "z": 1413
      },
      {
        "position": {
          "x": 110,
          "y": 92
        },
        "size": {
          "height": 15,
          "width": 15
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "embeds": [
          "_gKjM8NlgEfGvnMF0AcuMwg"
        ],
        "id": "_biQC9NctEfGRwJx1tbcBBg",
        "z": 1414,
        "parent": "_biQC89ctEfGRwJx1tbcBBg"
      },
      {
        "position": {
          "x": 75,
          "y": 169
        },
        "size": {
          "width": 816,
          "height": 188
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          },
          "name": {
            "text": "r1"
          }
        },
        "embeds": [
          "d1cb73f2-2d24-43d6-9712-fe3aa220901a",
          "_-pKiUNctEfGRwJx1tbcBBg",
          "_T0WtsNcuEfGRwJx1tbcBBg",
          "__opCUNctEfGRwJx1tbcBBg",
          "_W4XRQNcuEfGRwJx1tbcBBg",
          "282f7b96-3fe0-4b37-a4f5-a0ae42c2215a"
        ],
        "id": "_2meeQNctEfGRwJx1tbcBBg",
        "z": 1418,
        "parent": "_2md3MNctEfGRwJx1tbcBBg"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": 110,
          "y": 114
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": 0,
            "textVerticalAnchor": "top"
          }
        },
        "id": "_gKjM8NlgEfGvnMF0AcuMwg",
        "parent": "_biQC9NctEfGRwJx1tbcBBg",
        "z": 1419
      },
      {
        "position": {
          "x": 80,
          "y": 229
        },
        "size": {
          "height": 53,
          "width": 100
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "detenido",
            "fontSize": 11
          }
        },
        "embeds": [],
        "id": "_-pKiUNctEfGRwJx1tbcBBg",
        "parent": "_2meeQNctEfGRwJx1tbcBBg",
        "z": 1420
      },
      {
        "position": {
          "x": 302,
          "y": 208
        },
        "size": {
          "height": 95,
          "width": 538
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "running",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/vFuncionando = true; microondas_activo = ind_micro; grill_activo = ind_grill\r\nexit/ vFuncionando = false; microondas_activo = false; grill_activo = false"
          }
        },
        "embeds": [],
        "id": "__opCUNctEfGRwJx1tbcBBg",
        "parent": "_2meeQNctEfGRwJx1tbcBBg",
        "z": 1421
      },
      {
        "position": {
          "x": 119,
          "y": 320
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "282f7b96-3fe0-4b37-a4f5-a0ae42c2215a",
        "z": 1422,
        "embeds": [
          "60e3f9db-6bc4-4087-b7a9-155d63cb390f"
        ],
        "parent": "_2meeQNctEfGRwJx1tbcBBg"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": 119,
          "y": 335
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "60e3f9db-6bc4-4087-b7a9-155d63cb390f",
        "z": 1426,
        "parent": "282f7b96-3fe0-4b37-a4f5-a0ae42c2215a"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "__opCUNctEfGRwJx1tbcBBg"
        },
        "target": {
          "id": "_-pKiUNctEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "startStop\r\n"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": 1
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "_W4XRQNcuEfGRwJx1tbcBBg",
        "parent": "_2meeQNctEfGRwJx1tbcBBg",
        "z": 1427
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "282f7b96-3fe0-4b37-a4f5-a0ae42c2215a"
        },
        "target": {
          "id": "_-pKiUNctEfGRwJx1tbcBBg",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "46%",
              "dy": "79.245%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "d1cb73f2-2d24-43d6-9712-fe3aa220901a",
        "z": 1427,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "_2meeQNctEfGRwJx1tbcBBg"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_-pKiUNctEfGRwJx1tbcBBg"
        },
        "target": {
          "id": "__opCUNctEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "startStop"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "_T0WtsNcuEfGRwJx1tbcBBg",
        "parent": "_2meeQNctEfGRwJx1tbcBBg",
        "z": 1427
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_AVbaYNcvEfGRwJx1tbcBBg"
        },
        "target": {
          "id": "_2md3MNctEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "cerrar\r\n"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": 1
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "_FcvScNcvEfGRwJx1tbcBBg",
        "parent": "_biQC89ctEfGRwJx1tbcBBg",
        "z": 1427
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_biQC9NctEfGRwJx1tbcBBg"
        },
        "target": {
          "id": "_2md3MNctEfGRwJx1tbcBBg",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "49.027%",
              "dy": "9.322%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "3ed66e59-955a-4b35-9b68-70cac887f079",
        "z": 1427,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 117.5,
            "y": 68
          },
          {
            "x": 279,
            "y": 68
          }
        ],
        "parent": "_biQC89ctEfGRwJx1tbcBBg"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "_2md3MNctEfGRwJx1tbcBBg"
        },
        "target": {
          "id": "_AVbaYNcvEfGRwJx1tbcBBg"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "abrir\r\n"
              }
            },
            "position": {
              "distance": 0.4741891088060074,
              "offset": -20,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -5,
            "y": 378
          }
        ],
        "id": "_JIRJANcvEfGRwJx1tbcBBg",
        "parent": "_biQC89ctEfGRwJx1tbcBBg",
        "z": 1427
      },
      {
        "position": {
          "x": -2446,
          "y": 725
        },
        "size": {
          "width": 945,
          "height": 768
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 2
          },
          "name": {
            "text": "r_modo.4"
          }
        },
        "id": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2",
        "z": 1574,
        "embeds": [
          "b8b75cb8-749b-4b87-ac5b-77b60e000aaf",
          "5c187762-ce61-4ebb-9d67-2b8c92dde7b1",
          "cbe25d16-bd6e-45cf-a319-3644588f4637",
          "66c3cf9e-e0b2-4f89-817e-059e5a5f5582",
          "81fc1038-4a65-4e96-ac31-be1e46e3bd81",
          "ebb5e953-863e-41dc-bdd3-3cd71d0b1761"
        ]
      },
      {
        "position": {
          "x": -2379,
          "y": 778
        },
        "size": {
          "height": 93,
          "width": 212
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.microondas",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/ hito4.ind_micro=true; hito4.ind_grill=false\r\n"
          }
        },
        "id": "66c3cf9e-e0b2-4f89-817e-059e5a5f5582",
        "z": 1575,
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2"
      },
      {
        "position": {
          "x": -2116,
          "y": 760
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "81fc1038-4a65-4e96-ac31-be1e46e3bd81",
        "z": 1576,
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2",
        "embeds": [
          "b621ddb1-d027-4586-9791-3f6e4e9b1511"
        ]
      },
      {
        "position": {
          "x": -2405,
          "y": 1010
        },
        "size": {
          "height": 91,
          "width": 227
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.grill",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/ hito4.ind_grill=true; hito4.ind_micro=false\r\n"
          }
        },
        "id": "ebb5e953-863e-41dc-bdd3-3cd71d0b1761",
        "z": 1577,
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -2116,
          "y": 775
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "b621ddb1-d027-4586-9791-3f6e4e9b1511",
        "z": 1581,
        "parent": "81fc1038-4a65-4e96-ac31-be1e46e3bd81"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "ebb5e953-863e-41dc-bdd3-3cd71d0b1761",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "96.667%",
              "dy": "2.655%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "66c3cf9e-e0b2-4f89-817e-059e5a5f5582"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.modo [!hito4vFuncionando]"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "5c187762-ce61-4ebb-9d67-2b8c92dde7b1",
        "z": 1582,
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "81fc1038-4a65-4e96-ac31-be1e46e3bd81"
        },
        "target": {
          "id": "66c3cf9e-e0b2-4f89-817e-059e5a5f5582",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "51.887%",
              "dy": "47.312%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "cbe25d16-bd6e-45cf-a319-3644588f4637",
        "z": 1582,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "66c3cf9e-e0b2-4f89-817e-059e5a5f5582",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "6.132%",
              "dy": "98.925%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "ebb5e953-863e-41dc-bdd3-3cd71d0b1761"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.modo [!hito4vFuncionando]"
              }
            },
            "position": {
              "distance": 0.5078740157480315,
              "offset": -23,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "b8b75cb8-749b-4b87-ac5b-77b60e000aaf",
        "z": 1582,
        "parent": "bafbce94-ebe9-4be5-bdd2-9b29775cadc2"
      },
      {
        "position": {
          "x": -3678,
          "y": 886
        },
        "size": {
          "width": 1097,
          "height": 593
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 5
          },
          "name": {
            "text": "r_operacion.4"
          }
        },
        "id": "c5e3f2f4-d4cb-4117-b195-9353539dd578",
        "z": 1585,
        "embeds": [
          "f36ed0cb-2579-4776-9a33-14c53da169ad",
          "fab13557-2560-49cd-8d2a-b1833fd43c75",
          "9b706cf5-fc81-4faa-a4d8-5ef1f4cdb265",
          "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46",
          "0533c90d-cd7e-4365-8072-c06097f7f93d",
          "4f30900e-8aa4-4e0b-9a98-2ba84781fdcf"
        ]
      },
      {
        "position": {
          "x": -3675,
          "y": 951
        },
        "size": {
          "height": 321,
          "width": 999
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.puerta_cerrada",
            "fontSize": 11
          }
        },
        "id": "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46",
        "z": 1586,
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578",
        "embeds": [
          "be16863f-5c3a-49c2-a684-573cccf9def1"
        ]
      },
      {
        "position": {
          "x": -3637,
          "y": 919
        },
        "size": {
          "height": 15,
          "width": 15
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "0533c90d-cd7e-4365-8072-c06097f7f93d",
        "z": 1587,
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578",
        "embeds": [
          "c11472e4-c1b8-430f-9697-f8c7e2f67499"
        ]
      },
      {
        "position": {
          "x": -3672,
          "y": 996
        },
        "size": {
          "width": 993,
          "height": 273
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          },
          "name": {
            "text": "r15"
          }
        },
        "id": "be16863f-5c3a-49c2-a684-573cccf9def1",
        "z": 1587,
        "embeds": [
          "e76fe6d4-e3d5-407d-94c7-e10ca58b0147",
          "de175534-f1e1-432b-8dfb-38b34404e631",
          "f86f3ffd-016b-4363-9c9a-10c4f5f85cc8",
          "9ab31a6f-8f19-4165-b017-05f80570184d",
          "94a5654a-60cd-4b8d-b93c-5d8af2c0aac0",
          "2f86c333-b31a-477c-a999-2f140ff02e63",
          "25d1f0d7-bb8a-4d3e-ab3b-8bcdaf6051fe",
          "eb5f3380-6b69-479b-b576-e4ae99167c72",
          "c4fe54df-d91e-41eb-af8c-a97dd7c11078"
        ],
        "parent": "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "25d1f0d7-bb8a-4d3e-ab3b-8bcdaf6051fe"
        },
        "target": {
          "id": "eb5f3380-6b69-479b-b576-e4ae99167c72",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "2.23%",
              "dy": "50.526%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.startStop"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "e76fe6d4-e3d5-407d-94c7-e10ca58b0147",
        "z": 1588,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "eb5f3380-6b69-479b-b576-e4ae99167c72"
        },
        "target": {
          "id": "c4fe54df-d91e-41eb-af8c-a97dd7c11078",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "34.783%",
              "dy": "20.968%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.startStop"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "de175534-f1e1-432b-8dfb-38b34404e631",
        "z": 1589,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "position": {
          "x": -3544,
          "y": 1300
        },
        "size": {
          "height": 53,
          "width": 213
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.puerta_abierta",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/hito4vFuncionando=false\r\n"
          }
        },
        "id": "4f30900e-8aa4-4e0b-9a98-2ba84781fdcf",
        "z": 1589,
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "c4fe54df-d91e-41eb-af8c-a97dd7c11078",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "2.899%",
              "dy": "38.71%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "eb5f3380-6b69-479b-b576-e4ae99167c72",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "70.074%",
              "dy": "88.421%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.startStop"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f86f3ffd-016b-4363-9c9a-10c4f5f85cc8",
        "z": 1590,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -3081,
            "y": 1131
          }
        ],
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "c4fe54df-d91e-41eb-af8c-a97dd7c11078"
        },
        "target": {
          "id": "25d1f0d7-bb8a-4d3e-ab3b-8bcdaf6051fe",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "65%",
              "dy": "75.472%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "after 2s"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "9ab31a6f-8f19-4165-b017-05f80570184d",
        "z": 1591,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "2f86c333-b31a-477c-a999-2f140ff02e63"
        },
        "target": {
          "id": "25d1f0d7-bb8a-4d3e-ab3b-8bcdaf6051fe",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "46%",
              "dy": "79.245%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "94a5654a-60cd-4b8d-b93c-5d8af2c0aac0",
        "z": 1592,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "position": {
          "x": -3628,
          "y": 1177
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "2f86c333-b31a-477c-a999-2f140ff02e63",
        "z": 1593,
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1",
        "embeds": [
          "6b117af1-95a7-47cf-a5e4-a08b5bca8a3a"
        ]
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -3637,
          "y": 941
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": 0,
            "textVerticalAnchor": "top"
          }
        },
        "id": "c11472e4-c1b8-430f-9697-f8c7e2f67499",
        "z": 1593,
        "parent": "0533c90d-cd7e-4365-8072-c06097f7f93d"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -3628,
          "y": 1192
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "6b117af1-95a7-47cf-a5e4-a08b5bca8a3a",
        "z": 1594,
        "parent": "2f86c333-b31a-477c-a999-2f140ff02e63"
      },
      {
        "position": {
          "x": -3656,
          "y": 1047
        },
        "size": {
          "height": 53,
          "width": 100
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.detenido",
            "fontSize": 11
          }
        },
        "id": "25d1f0d7-bb8a-4d3e-ab3b-8bcdaf6051fe",
        "z": 1595,
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "position": {
          "x": -3411,
          "y": 1016
        },
        "size": {
          "height": 95,
          "width": 538
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.running",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/hito4vFuncionando = true;hito4.microondas_activo = hito4.ind_micro; hito4.grill_activo = hito4.ind_grill\r\nexit/ hito4vFuncionando = false; hito4.microondas_activo = false; hito4.grill_activo = false"
          }
        },
        "id": "eb5f3380-6b69-479b-b576-e4ae99167c72",
        "z": 1596,
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "position": {
          "x": -3082,
          "y": 1156
        },
        "size": {
          "height": 62,
          "width": 207
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "hito4.detenido_aviso",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/hito4.aviso_activo=true\nexit/hito4.aviso_activo=false"
          }
        },
        "id": "c4fe54df-d91e-41eb-af8c-a97dd7c11078",
        "z": 1597,
        "parent": "be16863f-5c3a-49c2-a684-573cccf9def1"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "0533c90d-cd7e-4365-8072-c06097f7f93d"
        },
        "target": {
          "id": "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "49.027%",
              "dy": "9.322%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "9b706cf5-fc81-4faa-a4d8-5ef1f4cdb265",
        "z": 1603,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "4f30900e-8aa4-4e0b-9a98-2ba84781fdcf"
        },
        "target": {
          "id": "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.cerrar\r\n"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "id": "fab13557-2560-49cd-8d2a-b1833fd43c75",
        "z": 1603,
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "d4408b46-91d7-4a9b-8c6a-eb88d76f8c46"
        },
        "target": {
          "id": "4f30900e-8aa4-4e0b-9a98-2ba84781fdcf"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "hito4.abrir\r\n"
              }
            },
            "position": {
              "distance": 0.4741891088060074,
              "offset": -20,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -3752,
            "y": 1205
          }
        ],
        "id": "f36ed0cb-2579-4776-9a33-14c53da169ad",
        "z": 1603,
        "parent": "c5e3f2f4-d4cb-4117-b195-9353539dd578"
      }
    ]
  },
  "genModel": {
    "generator": {
      "type": "create::c",
      "features": {
        "Outlet": {
          "targetProject": "",
          "targetFolder": "",
          "libraryTargetFolder": "",
          "skipLibraryFiles": "",
          "apiTargetFolder": ""
        },
        "LicenseHeader": {
          "licenseText": ""
        },
        "FunctionInlining": {
          "inlineReactions": false,
          "inlineEntryActions": false,
          "inlineExitActions": false,
          "inlineEnterSequences": false,
          "inlineExitSequences": false,
          "inlineChoices": false,
          "inlineEnterRegion": false,
          "inlineExitRegion": false,
          "inlineEntries": false
        },
        "OutEventAPI": {
          "observables": false,
          "getters": false
        },
        "IdentifierSettings": {
          "moduleName": "Statechart",
          "statemachinePrefix": "statechart",
          "separator": "_",
          "headerFilenameExtension": "h",
          "sourceFilenameExtension": "c"
        },
        "Tracing": {
          "enterState": false,
          "exitState": false,
          "generic": false
        },
        "Includes": {
          "useRelativePaths": false,
          "generateAllSpecifiedIncludes": false
        },
        "GeneratorOptions": {
          "userAllocatedQueue": false,
          "metaSource": false
        },
        "GeneralFeatures": {
          "timerService": false,
          "timerServiceTimeType": ""
        },
        "Debug": {
          "dumpSexec": false
        }
      }
    }
  }
}