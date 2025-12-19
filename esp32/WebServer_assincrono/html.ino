const char html[] PROGMEM = R"-**-(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LocalBus</title>
    <style>

        .fds{
            display: flex;
            flex-direction: column;
            gap: 15px;
            justify-content: center;
            align-items: center;
            border-radius: 10px;
            padding: 20px;
        }

        .inline label{
            min-width: 200px;
            display: inline-block;
            text-align: end;
        }

        .btn{
            width: 200px;
            padding: 5px;
            border-radius: 6px;
            cursor: pointer;
            font-size: 1em;
        }

    </style>
</head>
<body>
    
    <fieldset class="fds">
        <legend>Dados da rede móvel</legend>
        <div class="inline">
            <label for="edtSSID">Nome da Rede(SSID)</label>
            <input type="text" id="edtSSID" maxlength="15">
        </div>

        <div class="inline">
            <label for="edtPass">Senha</label>
            <input type="password" id="edtPass" maxlength="15">
        </div>

        <div class="inline">
            <button class="btn" id="btnSave">Salvar</button>
        </div>

    </fieldset>

</body>
<script>

      function postData(ssid,pass){
        const param = new URLSearchParams();
          param.append('ssid',ssid);
          param.append('pass',pass);
                  
          fetch('/action', {
              method: 'POST',
              body: param,
          })
            .then(response => {
              return response.text(); 
            })
            .then(textData => {
              const json = JSON.parse(textData)
              if(json.save){
                alert(`Rede ${ssid} salva com sucesso!`)
              }else{
                alert('Houve algum problema durante o processo de gravação, por favor entre em contato com um técnico ou resete o dispositivo e tente novamente.')
              }
              console.log(json);
            })
      }

    document.querySelector('#btnSave').addEventListener('click',()=>{
        const ssid = document.querySelector('#edtSSID').value
        const pass = document.querySelector('#edtPass').value
        if(confirm('Você deseja salvar estas informações?')){
          postData(ssid,pass)
        }
    })

</script>
</html>
)-**-";