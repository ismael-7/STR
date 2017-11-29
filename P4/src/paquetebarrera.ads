package paquetebarrera is
   -- Definir el tipo Barrera_t privado y limitado para poder usarlo fuera del paquete
      type Barrera_t(N: Integer) is limited private;
   -- Definir el procedimiento SincronizarEnBarrera con un par�metro de entrada salida de tipo Barrera_t
      procedure SincronizarEnBarrera(I:in out Barrera_t);
   -- Definir el procedimiento ResetearBarrera con un par�metro de entrada salida de tipo Barrera_t
      procedure ResetearBarrera(A: in out Barrera_t);
private
   -- Definir el objeto protegido Barrera_t. Recibir� un par�metro con el n�mero de tareas que bloquear� (10 por defecto)
   protected type Barrera_t(N: Integer) is
      -- Definir el procedimiento Entrando
      procedure Entrando;
      -- Definir la entrada Wait
      entry Wait;
      -- Definir el procedimiento Resetear
      procedure Resetear;
   -- Definir la regi�n privada del objeto protegido
   private
      -- Definir la variable Cont e inicializarla a 0
      Cont : Integer :=0;
      -- Definir la variable NumTareas e inicializarla a Tareas (par�metro de creaci�n del objeto protegido)
      NumTareas : Integer := N;
   -- Fin del objeto protegido
   end Barrera_t;
end paquetebarrera;
