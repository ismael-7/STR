with GNAT.IO;  use GNAT.IO;

package body paquete_buffer is
   -- Definir el cuerpo del objeto protegido Buffer_Acotado_t
       protected body Buffer_Acotado_t is
      -- A�adir la la entrada Pon (misma cabecera que en el fichero .ads)
        entry Pon(Item : in Integer)
         -- A�adir la condici�n de acceso a la entrada (barber�a no llena)
            when Nr_En_Buffer < Tama�o_Buffer is
          begin
         --A�adir Item a la posici�n Ultimo de Buffer
            Buffer(Ultimo)  := Item;
         -- Actualizar Ultimo
            Ultimo       := Ultimo + 1;
         -- Actualizar Cuenta
            Nr_En_Buffer := Nr_En_Buffer + 1;
            put_line("Insertado dato :" & integer'Image(Item));
          end;

      -- A�adir la la entrada Quita (misma cabecera que en el fichero .ads)
        entry Quita(Item : out Integer)
         -- A�adir la condici�n de acceso a la entrada (barber�a no vac�a)
            when Nr_En_Buffer > 0 is
          begin
         -- Almacenar en Item el contenido de la posici�n Primero de Buffer
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
