with GNAT.IO;  use GNAT.IO;
with paquetebarrera;  use paquetebarrera;

procedure Main is
   -- Definir una constante NumTareas para indicar el número de tareas que se bloquearán en la barrera
   NumTareas : Constant Integer:=10;
   -- Definir el tipo PBarrera_t de tipo puntero a Barrera_t
    type PBarrera_t is access all Barrera_t;
   -- Definir una variable B de tipo Barrera_t permitiendo que se acceda a su dirección de memoria (aliased). Usaremos NumTareas como parámetro constructor
    B: aliased Barrera_t(NumTareas);
   -- Dejinir el tipo tarea EntrandoEnBarrera con un parámetro B de tipo PBarrera_t
    task type EntrandoEnBarrera(B: PBarrera_t);
   -- Implementar el cuerpo del tipo tarea
   task body EntrandoEnBarrera
   is begin
      Put_Line("Entrando en la barrera");
      -- Invocar al procedimiento SincronizarEnBarrera pasando B.all como parámetro (B es un puntero a Barrera_t y el procedimiento recibe un Barrera_t)
      SincronizarEnBarrera(B.all);
      Put_Line("Saliendo de la barrera");
   end;
   -- Definir un array de tipo EntrandoEnBarrera con NumTareas elementos. Usar la dirección de B ('Access) como parámetro de EntrandoEnBarrera
      tareas: array(0..NumTareas) of EntrandoEnBarrera (B'Access);
begin
   null;
end Main;
