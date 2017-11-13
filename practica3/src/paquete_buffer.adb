with GNAT.IO;  use GNAT.IO;

package body paquete_buffer is
   -- Definir el cuerpo del objeto protegido Buffer_Acotado_t
       protected body Buffer_Acotado_t is
      -- Añadir la la entrada Pon (misma cabecera que en el fichero .ads)
        entry Pon(Item : in Integer)
         -- Añadir la condición de acceso a la entrada (barbería no llena)
            when Nr_En_Buffer < Tamaño_Buffer is
          begin
         --Añadir Item a la posición Ultimo de Buffer
            Buffer(Ultimo)  := Item;
         -- Actualizar Ultimo
            Ultimo       := Ultimo + 1;
         -- Actualizar Cuenta
            Nr_En_Buffer := Nr_En_Buffer + 1;
            put_line("Insertado dato :" & integer'Image(Item));
          end;

      -- Añadir la la entrada Quita (misma cabecera que en el fichero .ads)
        entry Quita(Item : out Integer)
         -- Añadir la condición de acceso a la entrada (barbería no vacía)
            when Nr_En_Buffer > 0 is
          begin
         -- Almacenar en Item el contenido de la posición Primero de Buffer
         Item         := Buffer(Primero);
         -- Actualizar Primero
         Primero      := Primero + 1;
         -- Actualizar Cuenta
         Nr_En_Buffer := Nr_En_Buffer - 1;
         put_line("Leyendo dato :" & integer'Image(Item));
           end;
   -- Fin del cuerpo del del objeto protegido Buffer_Acotado_t
      end Buffer_Acotado_t;
end paquete_buffer;
