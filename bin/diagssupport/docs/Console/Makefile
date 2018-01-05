.PHONY: default clean mostlyclean

COMMON_DIR = ../LaTeX/
PACKAGES = \
	$(COMMON_DIR)Smokey.sty \
	$(COMMON_DIR)mylistings/listings.sty

export TEXINPUTS := $(TEXINPUTS):$(COMMON_DIR)
LATEX = xelatex '\gdef\CommonDir{$(COMMON_DIR)}\input{$1}' -o $2

default: ConsoleUserGuide.pdf ConsoleDeveloperGuide.pdf

ConsoleUserGuide.pdf: \
	ConsoleBase.tex \
	ConsoleUserGuide.tex \
	$(PACKAGES)

ConsoleDeveloperGuide.pdf: \
	ConsoleBase.tex \
	ConsoleDeveloperGuide.tex \
	$(PACKAGES)

%.pdf: %.tex
	set -o errexit; \
	OldAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	$(call LATEX,$<,$@); \
	NewAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	if [ "$$OldAuxHash" != "$$NewAuxHash" ]; then \
		echo "******************************************************************************"; \
		$(call LATEX,$<,$@); \
	fi

clean: mostlyclean
	rm -f *.pdf

mostlyclean:
	rm -f *~
	rm -f *.aux *.log *.toc *.lof *.lot *.out
