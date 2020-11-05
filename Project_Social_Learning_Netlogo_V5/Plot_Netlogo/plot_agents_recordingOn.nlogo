extensions [ vid bitmap ]

;globals
;[
;  Max_X
;  Max_Y
;]

turtles-own
[
  detection
]

to setup

  ; clear interface
  clear-all
  reset-ticks
  file-close-all

  ;set Max_X 1000
  ;set Max_Y 1000

  ; create turtles

  create-turtles n-turtles + 2
  [
    ;set color one-of [red orange ]
    set color green
    set size 2
    set shape "robotitus"
  ]

  ask patches [ set pcolor 8 ];133 ]

 ; open file
  ; patches
  if (Experiment?)[ display-patches ]


end

to go

  tick

  if (vid:recorder-status = "inactive" )
  [
      vid:start-recorder
  ]

  ; read file
  ; turtles
  file-open "movement.csv";"movement.xls"

  let xxx 0
  let line 0
  let dummy 0
  let threshold (Patch_Diameter * max-pxcor / Max_X) / 2

  while [ not file-at-end?]
  [
    vid:record-view

    set line file-read-line

    ask turtles with [shape = "robotitus"]
    [
      ifelse ( detection != 0) [ set color red ]
      [set color green ]
    ]

    ask turtles with [shape = "circle"]
    [
      ask turtles with [shape = "robotitus" and distancexy [xcor] of myself [ycor] of myself < threshold]
      [
        set color one-of [red black]
      ]
    ]

    if (dummy > 2)
    [
      print display-turtles (line)
      ;set xxx display-turtles (line)
    ]

    set dummy dummy + 1

    if (mouse-down?)
      [
        vid:save-recording "2017 J of Ethology.mp4"
        print vid:recorder-status
        stop
      ]
  ]

  file-close

end

to display-patches

  let X 0
  let Y 0
  let k 0

  file-open "patches.csv"

  let line 0
  while [not file-at-end?]
  [
    set line file-read-line
    set X substring line 0 (position "," line)
    set Y substring line ((position "," line) + 1) (length line)

    ; convert string to number
    set X read-from-string X
    set Y read-from-string Y
    ask turtle k
    [
      set xcor X * max-pxcor / Max_X
      set ycor Y * max-pycor / Max_Y
      set shape "circle"
      set size Patch_Diameter * max-pxcor / Max_X
      ;set heading 90
    ]
    set k 1
  ]

  ; patch color
  ask turtle 0 [ set color black ]
  ask turtle 1 [ set color white ]

  file-close

end

to-report display-turtles [line]

  ; parameters:
  let X 0
  let Y 0
  let theta 0
  let value 0
  let det 0

  let t 2
  while [ t < (count turtles) ]
  [
    print line
    let pos-1 0
    let pos-2 0
    let i 0
    let j 0
    while [ i < 4]
    [
      set pos-2 position "," line
      ;print pos-2
      set value read-from-string substring line pos-1 pos-2

      if ( i = 0) [ set X value] ; set X
      if ( i = 1) [ set Y value] ; set Y
      if ( i = 2) [ set theta value * 180 / pi ] ; from radians to angle
      if ( i = 3) [ set det value ]

      ; remove value string from line
      set j 0
      while[j <= pos-2]
      [
        set line remove-item 0 line
        set j j + 1
      ]
      set i i + 1
    ]
    ; set turtles values
    ;write X write " " write Y write " " print theta

    ; ask turtles to set values
    ask turtle t
    [
      set xcor X * max-pxcor / Max_X
      set ycor Y * max-pycor / Max_Y
      set heading theta
      set detection det
    ]

    set t t + 1
  ]

  report " OK ;) "

end
@#$#@#$#@
GRAPHICS-WINDOW
167
11
833
678
-1
-1
12.902
1
10
1
1
1
0
1
1
1
0
50
0
50
0
0
1
ticks
30.0

BUTTON
8
10
72
43
NIL
Setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
76
10
139
43
NIL
go
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
7
54
139
87
n-turtles
n-turtles
0
100
10.0
10
1
NIL
HORIZONTAL

SWITCH
7
91
140
124
Experiment?
Experiment?
0
1
-1000

SLIDER
5
129
139
162
Patch_Diameter
Patch_Diameter
0
500
150.0
10
1
NIL
HORIZONTAL

INPUTBOX
5
182
63
242
Max_X
500.0
1
0
Number

INPUTBOX
72
182
138
242
Max_Y
500.0
1
0
Number

@#$#@#$#@
## WHAT IS IT?

(a general understanding of what the model is trying to show or explain)

## HOW IT WORKS

(what rules the agents use to create the overall behavior of the model)

## HOW TO USE IT

(how to use the model, including a description of each of the items in the Interface tab)

## THINGS TO NOTICE

(suggested things for the user to notice while running the model)

## THINGS TO TRY

(suggested things for the user to try to do (move sliders, switches, etc.) with the model)

## EXTENDING THE MODEL

(suggested things to add or change in the Code tab to make the model more complicated, detailed, accurate, etc.)

## NETLOGO FEATURES

(interesting or unusual features of NetLogo that the model uses, particularly in the Code tab; or where workarounds were needed for missing features)

## RELATED MODELS

(models in the NetLogo Models Library and elsewhere which are of related interest)

## CREDITS AND REFERENCES

(a reference to the model's URL on the web if it has one, as well as any other necessary credits, citations, and links)
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

fish 3
true
0
Polygon -7500403 true true 137 105 124 83 103 76 77 75 53 104 47 136
Polygon -7500403 true true 226 194 223 229 207 243 178 237 169 203 167 175
Polygon -7500403 true true 137 195 124 217 103 224 77 225 53 196 47 164
Polygon -7500403 true true 40 123 32 109 16 108 0 130 0 151 7 182 23 190 40 179 47 145
Polygon -7500403 true true 45 120 90 105 195 90 275 120 294 152 285 165 293 171 270 195 210 210 150 210 45 180
Circle -1184463 true false 244 128 26
Circle -16777216 true false 248 135 14
Line -16777216 false 48 121 133 96
Line -16777216 false 48 179 133 204
Polygon -7500403 true true 241 106 241 77 217 71 190 75 167 99 182 125
Line -16777216 false 226 102 158 95
Line -16777216 false 171 208 225 205
Polygon -1 true false 252 111 232 103 213 132 210 165 223 193 229 204 247 201 237 170 236 137
Polygon -1 true false 135 98 140 137 135 204 154 210 167 209 170 176 160 156 163 126 171 117 156 96
Polygon -16777216 true false 192 117 171 118 162 126 158 148 160 165 168 175 188 183 211 186 217 185 206 181 172 171 164 156 166 133 174 121
Polygon -1 true false 40 121 46 147 42 163 37 179 56 178 65 159 67 128 59 116

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

mouse side
false
0
Polygon -7500403 true true 38 162 24 165 19 174 22 192 47 213 90 225 135 230 161 240 178 262 150 246 117 238 73 232 36 220 11 196 7 171 15 153 37 146 46 145
Polygon -7500403 true true 289 142 271 165 237 164 217 185 235 192 254 192 259 199 245 200 248 203 226 199 200 194 155 195 122 185 84 187 91 195 82 192 83 201 72 190 67 199 62 185 46 183 36 165 40 134 57 115 74 106 60 109 90 97 112 94 92 93 130 86 154 88 134 81 183 90 197 94 183 86 212 95 211 88 224 83 235 88 248 97 246 90 257 107 255 97 270 120
Polygon -16777216 true false 234 100 220 96 210 100 214 111 228 116 239 115
Circle -16777216 true false 246 117 20
Line -7500403 true 270 153 282 174
Line -7500403 true 272 153 255 173
Line -7500403 true 269 156 268 177

mouse top
true
0
Polygon -7500403 true true 238 156 255 147 260 132 257 104 241 86 234 63 243 52 260 63 278 101 282 146 276 167 270 191 273 210 283 217 279 202 282 180 293 144 287 100 273 65 254 44 238 39 226 48 221 68 228 89 238 106 246 117 246 132 232 137
Polygon -7500403 true true 78 180 62 184 35 173 16 161 4 150 16 140 33 127 60 117 80 120
Polygon -7500403 true true 75 181 75 121 105 105 166 110 215 107 240 135 240 165 213 194 165 190 105 195
Polygon -7500403 true true 69 133 68 116 64 107 65 101 74 98 82 106 79 115 80 129
Polygon -7500403 true true 69 167 68 184 64 193 65 199 74 202 82 194 79 185 80 171
Polygon -16777216 true false 28 137 32 129 40 127 45 131 47 134
Polygon -16777216 true false 28 163 32 171 40 173 45 169 47 166
Polygon -16777216 true false 6 150 14 157 14 144
Line -7500403 true 17 139 10 105
Line -7500403 true 22 140 20 113
Line -7500403 true 22 140 31 99
Line -7500403 true 22 160 31 201
Line -7500403 true 22 160 20 187
Line -7500403 true 17 161 10 195

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

robotitus
true
0
Circle -16777216 true false 33 33 234
Circle -1 true false 44 44 212
Polygon -7500403 true true 210 150
Polygon -6459832 true false 60 150 90 90 165 60 225 75 165 45 75 75 60 150
Polygon -6459832 true false 180 120 180 150 225 120 180 90 180 150
Circle -7500403 true true 174 99 42
Rectangle -6459832 true false 120 180 180 195

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

test_fish
true
0
Polygon -7500403 true true 165 255 180 300 150 240 165 240
Polygon -7500403 false true 105 150
Polygon -1 true false 150 15 120 60 105 105 105 135 120 195 135 225 150 255 135 300 165 255 165 195 180 90 165 60
Polygon -7500403 true true 150 165
Polygon -955883 true false 180 120 195 165 150 105 180 120
Polygon -7500403 true true 165 150
Polygon -955883 true false 105 120 90 165 120 120 105 120
Circle -7500403 true true 60 75 0
Circle -1 true false 103 88 62
Circle -1 true false 118 73 62
Circle -1 true false 148 103 32
Rectangle -1 true false 150 255 165 270
Polygon -1 true false 165 285
Polygon -1 true false 45 135
Polygon -7500403 true true 180 90 150 240 165 105 165 75
Polygon -7500403 true true 120 105 135 225 105 120 120 60
Polygon -7500403 true true 135 45 150 45 165 60 135 45 120 60 150 45

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270
@#$#@#$#@
NetLogo 6.0.4
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180
@#$#@#$#@
0
@#$#@#$#@
