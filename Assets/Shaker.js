var startTime : float;
var shakeTime : float;
var shakenUp : boolean = false;

var	resetTimer : float = 10;

var shakeItImage : Texture;
var pickItImage : Texture;
var winImage : Texture;
var loseImage : Texture;

var buzzerSound : AudioClip;
var canOpenSound : AudioClip;
var dingSound : AudioClip;
var explosionSound : AudioClip;
var shakeSound : AudioClip;


function Start () {
	enabled = true;
	renderer.material.mainTexture = shakeItImage;

	startTime = 0;
	shakeTime = 0;
	shakenUp = false;
}

function Update () {
	if(!shakenUp) {
		if(Input.GetKeyDown("a")) {
			startTime = Time.time;
			AudioSource.PlayClipAtPoint(shakeSound, transform.position);
		}

		if(Input.GetKeyUp("a")) {
			shakeTime = Time.time - startTime;
			renderer.material.mainTexture = pickItImage;
			shakenUp = true;
			AudioSource.PlayClipAtPoint(dingSound, transform.position);
		}
	} else {
		shakeTime -= Time.deltaTime;
		if(Input.GetKeyDown("a")) {
			if(shakeTime > 0) {
				renderer.material.mainTexture = loseImage;
				AudioSource.PlayClipAtPoint(explosionSound, transform.position);

			} else {
				renderer.material.mainTexture = winImage;
				AudioSource.PlayClipAtPoint(canOpenSound, transform.position);

			}

			WaitAndReset();
		}

	}
}

function WaitAndReset() {
	enabled = false;
	yield WaitForSeconds(resetTimer);
	Start();
}