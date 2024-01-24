new Vue({
    el: '#desafio',
    data: {
        valor: ''
    },
    methods:{
        alerta(){
            alert('ALERTA!!')
        },
        alterarValor(e){
            this.valor = e.target.value
        }
    }
})