# User stories
Este documento contiene las historias de usuario que se han definido para el proyecto con sus criterios de aceptación.

## US08: Verificación de la humedad del suelo

**Como** agricultor  
**Quiero** contar con indicador de la humedad del suelo de cada uno de mis cultivos  
**Para** asegurarme que cada uno de los suelos esté en el estado correcto para no arruinar los cultivos

### Criterios de aceptación

- **Escenario 1: Suelo con humedad dentro de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la humedad del suelo  
  - Y la humedad del suelo esté dentro de los parámetros aceptables  
  - Entonces se podrán ver los datos importantes del suelo  
  - Y en la parte inferior aparecerá un mensaje, indicando que el suelo se encuentra con la humedad favorable

- **Escenario 2: Suelo con humedad ligeramente fuera de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la humedad del suelo  
  - Y la humedad del suelo esté ligeramente fuera de los parámetros aceptables  
  - Entonces se podrán ver los datos importantes del suelo  
  - Y en la parte inferior aparecerá un mensaje de precaución, indicando que el suelo no se encuentra en un estado aceptable y que requiere atención

- **Escenario 3: Suelo con humedad fuera de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la humedad del suelo  
  - Y la humedad del suelo esté muy por fuera de los parámetros aceptables  
  - Entonces aparecerá un mensaje de peligro, indicando que el suelo necesita atención urgente y que se pueden hechar a perder los cultivos  
  - Y en la parte inferior se encontrarán los datos del cultivo

- **Escenario 4: Suelo inundado**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la humedad del suelo  
  - Y el suelo se encuentra inundado  
  - Entonces aparecerá un mensaje, indicando que el suelo se encuentra en una situación no favorable  
  - Y en la parte inferior se encontrarán los datos del cultivo  
  - Y aparecerá el botón "Acciones recomendadas"

- **Escenario 5: Suelo seco**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la humedad del suelo  
  - Y el suelo se encuentra muy seco  
  - Entonces aparecerá un mensaje, indicando que el suelo se encuentra en una situación no favorable  
  - Y en la parte inferior se encontrarán los datos del cultivo  
  - Y aparecerá el botón "Acciones recomendadas"


## US09: Verificación de la temperatura del suelo

**Como** agricultor  
**Quiero** contar con indicador de la temperatura del suelo de cada uno de mis cultivos  
**Para** asegurarme que el suelo en donde se encuentran mis cultivos se encuentren con la temperatura correcta para no arruinar los cultivos

### Criterios de aceptación

- **Escenario 1: Suelo con temperatura dentro de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la temperatura del suelo  
  - Y la temperatura del suelo esté dentro de los parámetros aceptables  
  - Entonces se podrán ver los datos importantes del suelo  
  - Y en la parte inferior aparecerá un mensaje, indicando que el suelo se encuentra con la temperatura favorable

- **Escenario 2: Suelo con temperatura ligeramente fuera de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la temperatura del suelo  
  - Y la temperatura del suelo esté ligeramente fuera de los parámetros aceptables  
  - Entonces se podrán ver los datos importantes del suelo  
  - Y en la parte inferior aparecerá un mensaje de precaución, indicando que el suelo no se encuentra con una temperatura aceptable y que requiere atención

- **Escenario 3: Suelo con temperatura fuera de los parámetros normales**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la temperatura del suelo  
  - Y la temperatura del suelo esté muy por fuera de los parámetros aceptables  
  - Entonces aparecerá un mensaje de peligro, indicando que el suelo necesita atención urgente y que se pueden hechar a perder los cultivos  
  - Y en la parte inferior se encontrarán los datos del cultivo

- **Escenario 4: Suelo en llamas**  
  - Dado que el agricultor se encuentra en la página "Detalles del suelo"  
  - Cuando el agricultor quiera visualizar la temperatura del suelo  
  - Y el suelo se encuentra en llamas  
  - Entonces aparecerá un mensaje de peligro, indicando que el suelo está en llamas  
  - Y en la parte inferior se encontrarán los datos del cultivo  
  - Y aparecerá el botón "Acciones recomendadas"


## US12: Interacción con el riego automático
**Como** agricultor  
**Quiero** poder activar y desactivar el riego automático  
**Para** tener mayor control con el agua que se está utilizando para el regado de cultivos

### Criterios de aceptación
- **Escenario 1: Activar regado automático**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Y el regado automático está desactivado  
  - Cuando el agricultor haga click en el switch "Toggle Regado"  
  - Entonces el regado automático se activará para el cultivo seleccionado  
  - Y aparecerá un mensaje de confirmación, indicando que el regado automático ha sido activado

- **Escenario 2: Desactivar regado automático**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Y el regado automático está activado  
  - Cuando el agricultor haga click en el switch "Toggle Regado"  
  - Entonces el regado automático se desactivará para el cultivo seleccionado  
  - Y aparecerá un mensaje de confirmación, indicando que el regado automático ha sido desactivado

- **Escenario 3: Desactivar regado automático mientras se está regando**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Y el regado automático está activado  
  - Y actualmente se está regando  
  - Cuando el agricultor haga click en el switch "Toggle Regado"  
  - Entonces aparecerá un mensaje, indicando que se está regando en este momento, junto con un botón para confirmar la desactivación

- **Escenario 4: Activar regado automático para todos los cultivos**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Cuando el agricultor haga click en el botón "Activar Regado de todos los cultivos"  
  - Entonces aparecerá un mensaje, indicando se ha activado el regado automático para todos los cultivos

- **Escenario 5: Desactivar regado automático para todos los cultivos**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Cuando el agricultor haga click en el botón "Desactivar Regado de todos los cultivos"  
  - Entonces aparecerá un mensaje, indicando se ha desactivado el regado automático para todos los cultivos

- **Escenario 6: Desactivar regado automático para todos los cultivos mientras al menos 1 se está actualmente regando**  
  - Dado que el agricultor se encuentra en la página "Cultivos"  
  - Cuando el agricultor haga click en el botón "Desactivar Regado de todos los cultivos"  
  - Y al menos 1 cultivo se esté regando  
  - Entonces aparecerá un mensaje, indicando que se está regando en este momento, junto con un botón para confirmar la desactivación




