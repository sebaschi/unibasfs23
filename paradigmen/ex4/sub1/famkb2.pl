% Division: Canina, Tribe: Canina
canina(canis)
% Division: Vulpini, Tribe: Vulpes
canine(vulpes_vulpes, vulpes, vulpini).
canine(vulpes_lagopus, vulpes, vulpini).
canine(vulpes_macrotis, vulpes, vulpini).
canine(vulpes_zerda, vulpes, vulpini).

% Division: Urocyonini, Tribe: Urocyon
canine(urocyon_cinereoargenteus, urocyon, urocyonini).
canine(urocyon_littoralis, urocyon, urocyonini).

% Division: Lycaonini, Tribe: Lycaon
canine(lycaon_pictus, lycaon, lycaonini).

% Additional canines
canine(african_wild_dog, lycaon, lycaonini).
canine(dhole, cuon, Canina).
canine(bush_dog, speothos, Canina).
canine(raccoon_dog, nyctereutes, Canina).
canine(short-eared_dog, atelocynus, Canina).
canine(dusicyon, dusicyon, Canina).
canine(ethiopian_wolf, canis, Canina).
canine(maned_wolf, chrysocyon, Canina).
canine(sechuran_fox, lycalopex, Canina).
canine(hoary_fox, lycalopex, Canina).
canine(anda_fox, lycalopex, Canina).
canine(culpeo, lycalopex, Canina).
canine(darwins_fox, lycalopex, Canina).

% Rule to check if a canine is part of a given division and genus
partOf(Species, Genus, Division) :-
    canine(Species, Genus, Division).

% Example usage:
% partOf(lycaon, Canis, Canina).  % true
% partOf(cana, X, Y).            % X = vulpes, Y = vulpini

