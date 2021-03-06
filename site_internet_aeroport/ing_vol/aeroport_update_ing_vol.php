<!DOCTYPE html>
<html lang="fr" dir="ltr">
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="../css/style_compte.css" type="text/css" />
    <title>Update d'un vol</title>
  </head>
  <body>
    <?php
    $link = new mysqli('localhost',$_POST['identifiant'],$_POST['password']);
    if ($link->connect_errno) {
    die ("Erreur de connexion : errno: " . $link->errno .
                      "error:" . $link->error);
    }

    $link->select_db('aeroport') or die("Erreur selection BD: ".$link->error);

    $num_vol = $_POST['vol'];

    /*Vérification du numéro de l'avion*/
    $num = $link->query("SELECT * FROM Vol WHERE num_vol = $num_vol") or die("Search Error:" .$link->error());
    $iterator = $num->fetch_assoc();

    if(empty($iterator))
    {
      ?>
        <div align="center">
          <h3>Le numéro de vol entré n'existe pas.</h3>
          <table>
            <form action="aeroport_update_choix_vol.php" method="post">
              <input type="hidden" name="identifiant" value="<?php echo $_POST['identifiant'] ?>">
              <input type="hidden" name="password" value="<?php echo $_POST['password'] ?>">
              <input type="hidden" name="choice" value="<?php echo $_POST['choice'] ?>">
              <input type="hidden" name="choix" value="<?php echo $_POST['choix'] ?>">
              <input type="image" src = "../images/button_retour.png" width="11%">
            </form>
          </table>
        </div>
      <?php
      $link->close();
      exit();
    }

    if($_POST['choice']=="horaires")
    {
      $horaires = $_POST['horaires'];
      $link->query("UPDATE Vol SET horaires = '$horaires' WHERE num_vol = '$num_vol'") or die("Update Error:" .$link->error());
    }
    else {
      $date = $_POST['date'];
      $link->query("UPDATE Vol SET date_vol = '$date' WHERE num_vol = '$num_vol'") or die("Update Error:" .$link->error());
    }

    $link->close();
    ?>
    <div align="center">
      <h3>La mise à jour a été effectué avec succès.</h3>
      <form action="../connexion_employe/aeroport_verification_employe.php" method="post">
        <input type="hidden" name="identifiant" value="<?php echo $_POST['identifiant'] ?>">
        <input type="hidden" name="password" value="<?php echo $_POST['password'] ?>">
        <input type="image" src = "../images/button_choice.png" width="11%">
      </form>
    </div>
  </body>
</html>
