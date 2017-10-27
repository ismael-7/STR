package paquete_buffer is
   -- Definir e inicializar la constante Tamanio_Buffer de tipo entero
      Tama�o_Buffer : constant Integer := 7;
   -- Definir el tipo Index_t que sea un rango entre 0 a Tamanio_Buffer-1 (usar mod Tamanio_Buffer)
      type Index_t is mod Tama�o_Buffer;
   --Definir un subtipo Cuenta_t basado en el tipo Natural que vaya de 0 a Tamanio_Buffer
      subtype Cuenta_t is Natural range 0 .. Tama�o_Buffer;
   -- Definir el tipo Buffer_t como un array de enteros en el rango Index_t
      type Buffer_t is array (Index_t) of Integer;
   -- Definir el objeto protegido Buffer_Acotado_t
      protected type Buffer_Acotado_t is
      -- A�adir la entrada Pon que reciva el dato a insertar
         entry Pon   (Item : in  Integer);
      -- A�adir la entrada Quita que devuelva el dato le�do
         entry Quita (Item :  out Integer);
   -- definir la zona privada del objeto
      private
      -- Definir e inicializar el atributo Primero de tipo Index_t (usar Index_t'First para la inicializaci�n)
         Primero      : Index_t  := Index_t'First;     
      -- Definir e inicializar el atributo Ultimo de tipo Index_t (usar Index_t'First para la inicializaci�n)
         Ultimo       : Index_t  := Index_t'First;
      -- Definir e inicializar el atributo Cuenta de tipo Cuenta_t
         Nr_En_Buffer : Cuenta_t := 0;
      -- Definir el atributo Buffer de tipo Buffer_t
         Buffer       : Buffer_t;
   --Final del objeto protegido Buffer_Acotado_t
      end;

end paquete_buffer;
