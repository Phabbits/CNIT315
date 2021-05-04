<?php
//Includes

//source - https://www.benmarshall.me/php-mysql-connect/

define('DB_SERVER', 'localhost');
define('DB_USERNAME', 'gabriel');
define('DB_PASSWORD', 'supersecureplaintext');

// get values from form
if (isset($_POST['player_name'])){
  $player_name = $_POST['player_name'];
  $score = $_POST['score'];
}
if (isset($_POST['seed'])){
  $seed = $_POST['seed'];
  $version = $_POST['version'];
}
else{
    // defualts to allow access from a browser
    $seed = 1;
    $version = 0.01;
}

// always wrap PDO operations in a try/catch
try{
  // only make a connection when it is needed
  // no guarantee of a future request
  $conn = new PDO('mysql:host=localhost; dbname=class', DB_USERNAME, DB_PASSWORD);
  $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

  // ensure that database is setup
  if (!sql_table_exists($conn, 'score')){
    $stmt = $conn->prepare('CREATE TABLE score (id INT NOT NULL AUTO_INCREMENT, player_name VARCHAR(80) NOT NULL, score INT NOT NULL, seed INT, version DECIMAL(6,4), played DATE, PRIMARY KEY (id));');
    $stmt->execute();
    echo "Created score table successfully!\n";
  }

  if (isset($player_name)){
    // player was given, so assume to add a score
    sql_add_score($conn, $player_name, $score, $seed, $version);
    echo "Added new score! Congrats, $player_name, you scored $score\n\n";
  }
  else{
    // no details given, so assume request to get highscores
    sql_echo_scores($conn, $seed, $version);
  }
}
catch(PDOException $e){
  echo 'ERROR: ' . $e->getMessage();
}

// Functions
function sql_table_exists($conn, $name){
  // cannot use a prepare statement, because that always adds ''
  // Caution! should only be used internally
  try{
    $result = $conn->query("DESCRIBE `$name`");
  }
  catch(PDOException $e){
    return false;
  }

  return $result !== false;
}

function sql_add_score($conn, $player_name, $score, $seed, $version){
  $stmt = $conn->prepare('INSERT INTO score (player_name, score, seed, version, played) VALUES (:player_name, :score, :seed, :version, CURDATE())');
  $stmt->execute(array(':player_name' => $player_name, ':score' => $score, ':seed' => $seed, ':version' => $version));
}

function sql_echo_scores($conn, $seed, $version){
  $stmt = $conn->prepare('SELECT player_name, score FROM score WHERE seed = :seed AND version = :version ORDER BY score');
  $stmt->execute(array(':seed' => $seed, ':version' => $version));

  // get array with all result rows
  $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

  $rank = 1;
  foreach ($rows as $row){
    echo " " . $rank . "   " . $row["score"] . "      " . $row["player_name"] . "\n";
    $rank = $rank + 1;
  }
}
?>
