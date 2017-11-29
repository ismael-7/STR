package body paquetebarrera is
   -- Definir el cuerpo del objeto Barrera_t
   protected body Barrera_t is
      -- Implementar el procedimiento Entrando del objeto protegido que se encargará de incrementar el contador
      procedure Entrando is
      begin
         Cont := Cont +1;
      end;

      -- Implementar la entrada Wait incluyendo la condición de paso (no han llegado a la barrera el número de tareas indicado). En el código, no hace nada, sólo bloquea.
      entry Wait when Cont = NumTareas is
      begin
         null;
      end;


      -- Implementar el procedimiento Resetear que pone el contador a 0
      procedure Resetear is
      begin
         Cont:=0;
      end;

   -- Fin del objeto protegido
   end Barrera_t;

   -- Implementación del procedimiento SincronizarEnBarrera
   procedure SincronizarEnBarrera(I:in out Barrera_t) is
   begin

      -- Invoca al procedimiento Entrando de la barrera
      I.Entrando;
      -- Invoca a la entrada Wait de la barrera
      I.Wait;
   -- Fin del procedimiento SincronizarEnBarrera
   end;

   -- Implementación del procedimiento SincronizarEnBarrera
   procedure ResetearBarrera(A: in out Barrera_t) is
   begin

      -- Invoca al procedimiento Resetear de la barrera
      A.Resetear;
   -- Fin del procedimiento ResetearBarrera
   end;
end paquetebarrera;
