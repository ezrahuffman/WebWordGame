function addLetter(btn){
	var curr = $("#display-word").html();
	var letter = $(btn).html();
	if (curr == ""){
		curr = letter;
	}
	else {
		curr = curr + " " + letter;
	}
	$(btn).prop("disabled",true);
	$("#display-word").html(curr);
}

function makeButtons(list){
	var str = "";
	for(var i = 1; i <= 9; i++){
		str = "#btn" + i;
		$(str).html(list[i-1]);
		$(str).click(function(){
			//addLetter(list[i-1]);
			$(this).prop("disabled",true);
		});
	}
}


function resetInterface(){
	for(var i = 1; i <= 9; i++){
		str = "#btn" + i;
		$(str).prop("disabled",false);
	}
	$("#display-word").html("");
}

function showSolution(data){
	var str = "";
	if ($("#solution").html() != ""){
		$("#solution").html("");
	} else{
		for (var i = 0; i < data.length; i++){
			str += data[i] + ", ";
		}
	
		$("#solution").html(str);
	}
}

$(document).ready(function(){
	var sol = [];
	$.get("/list", {}, function(response){
		var data = JSON.parse(response)[0];
		var list = [];
		for (var i in data){
			var letter = String.fromCharCode(parseInt(data[i]));
			list.push(letter);
		}
		var str = list.toString().replace(/\,/g, '');
		$.get("/solution", {letters: str}, function(response){
			var data = JSON.parse(response);
			sol = data;
		});
		makeButtons(list);
	});
	
	$("#clearWord").click(function(){
		resetInterface();
	});

	$("#newGame").click(function(){
		resetInterface();
		$("#correct").html("");
	});

	$("#solutionBtn").click(function(){
		showSolution(sol);
	});

	$("#checkWord").click(function(){
		var attempt = $("#display-word").html();
		attempt = attempt.replace(/\s/g, '');

		$.get("/checkWord", {word: attempt}, function(response){
			var answer = JSON.parse(response);
			var word = answer["word"];
			var valid = answer["valid"];

			resetInterface();

			if (valid){
				var curr = $("#correct").html();
				if (curr == ""){
					curr = word;
				}
				else{
					curr = curr + ", " + word;
				}
				$("#correct").html(curr);
			}

		});
	});
});
